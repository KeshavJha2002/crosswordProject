#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fstream>
#include <thread>
#include "showf.hpp"
#include "updatef.hpp"
#include "clue.hpp"
#include "createArray.hpp"
#include "readTF.hpp"
#include "play.hpp"
#include <map>
#include <arpa/inet.h>

using namespace std;

class Client {
public:
    Client(const char* serverIp, int serverPort) : serverIp(serverIp), serverPort(serverPort) {
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket < 0) {
            cerr << "Error creating socket" << endl;
            return;
        }

        // Connect to the server
        struct sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(serverPort);
        inet_pton(AF_INET, serverIp, &serverAddress.sin_addr);
        if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
            cerr << "Error connecting to the server" << endl;
            return;
        }
    }

    void start() {
        if (clientSocket < 0) {
            cerr << "Client socket is not properly initialized" << endl;
            return;
        }

        while (true) {
            int choice;
            cout << "Choose an option:" << endl;
            cout << "1. Login" << endl;
            cout << "2. Register" << endl;
            cout << "3. Exit" << endl;
            cin >> choice;
            switch (choice) {
                case 1:
                    login("login");
                    break;
                case 2:
                    registerUser("register");
                    break;
                case 3:
                    exit(0);
                default:
                    cout << "Please choose a valid option." << endl;
                    break;
            }
        }

        close(clientSocket);
    }

private:
    int clientSocket;
    const char* serverIp;
    int serverPort;

    void login(string choice) {
        string username, password;
        cout << "Enter your desired username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;
        string hashedPassword = hashPassword(password);

        // Launch a thread to handle the login
        thread loginThread(&Client::handleLogin, this, choice, username, hashedPassword);
        loginThread.join();
    }

    void handleLogin(string choice, string username, string hashedPassword) {
        send(clientSocket, choice.c_str(), 64, 0);
        send(clientSocket, username.c_str(), 128, 0);
        send(clientSocket, hashedPassword.c_str(), 512, 0);

        char buffer[4];
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = recv(clientSocket, buffer, 4, 0);
        string res = buffer;
        if (res == "true") {
            printWelcomeMessage();
        } else {
            cerr << "Error reading from the server" << endl;
        }
    }

    void registerUser(string choice) {
        string username, password;
        cout << "Enter your desired username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;
        string hashedPassword = hashPassword(password);

        // Launch a thread to handle registration
        thread registrationThread(&Client::handleRegistration, this, choice, username, hashedPassword);
        registrationThread.join();
    }

    void handleRegistration(string choice, string username, string hashedPassword) {
        send(clientSocket, choice.c_str(), 64, 0);
        send(clientSocket, username.c_str(), 128, 0);
        send(clientSocket, hashedPassword.c_str(), 512, 0);

        char buffer[4];
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = recv(clientSocket, buffer, 4, 0);
        string res = buffer;
        if (res == "true") {
            printWelcomeMessage();
        } else {
            cerr << "Error reading from the server" << endl;
        }
    }

    void printWelcomeMessage() {
        cout << "Hello warrior." << endl;
        int gameOver = 0;
        string filename = "cw.txt"; // default text file
        vector<vector<string>> board;
        ifstream crossword;
        int x, y, words;
        vector<Clue> clues;

        cout << "Choose the crossword board you want to play with:\n";
        cout << "1. CrossBoard1(EASY)\n";
        cout << "2. CrossBoard2(MEDIUM)\n";
        cout << "3. CrossBoard3(HARD)\n";
        cout << "Enter the number of CrossBoard You want to play with: ";

        int boardChoice;
        if (!(cin >> boardChoice)) {
            cerr << "Invalid input. Please enter a number." << endl;
            return;
        }

        cin.clear();
        while (cin.get() != '\n');

        switch (boardChoice) {
            case 1:
                filename = "cw.txt";
                break;
            case 2:
                filename = "crossword1.txt";
                break;
            case 3:
                filename = "crossword2.txt";
                break;
            default:
                cerr << "Invalid choice. Using the default board." << endl;
                filename = "cw.txt";
                break;
        }

        crossword.open(filename);
        if (!crossword.is_open()) {
            cerr << "Error opening game board file: " << filename << endl;
            return;
        }

        cout << "Loading the game board..." << endl;
        crossword >> x >> y >> words;
        cout << "Game is " << x << " rows x " << y << " cols with " << words << " words" << endl;
        clues = readTF(crossword, words);
        crossword.close();

        board = createArray(x, y);
        play(board, words, clues, x, y, gameOver);
    }

    string hashPassword(const string& password) {
        string hashedPassword;
        for (char c : password) {
            hashedPassword += c;
            hashedPassword += to_string(static_cast<int>(c));
        }
        return hashedPassword;
    }
};

int main() {
    Client client("127.0.0.1", 12345);
    client.start();
    return 0;
}
