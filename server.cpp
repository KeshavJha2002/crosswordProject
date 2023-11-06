#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <fstream>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <vector>
#include "showf.hpp"
#include "updatef.hpp"
#include "clue.hpp"
#include "createArray.hpp"
#include "readTF.hpp"
#include "play.hpp"
#include <arpa/inet.h>

using namespace std;

class Server {
public:
    Server(int port) : serverPort(port) {
    }

    void start() {
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket < 0) {
            cerr << "Error creating socket" << endl;
            return;
        }

        struct sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(serverPort);

        if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
            cerr << "Error binding socket" << endl;
            return;
        }

        listen(serverSocket, 5);
        cout << "Server is listening on port " << serverPort << "..." << endl;

        while (true) {
            int clientSocket;
            struct sockaddr_in clientAddress;
            socklen_t clientAddressLength = sizeof(clientAddress);
            clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
            if (clientSocket < 0) {
                cerr << "Error accepting client connection" << endl;
                continue;  // Continue listening for other clients
            }

            thread clientThread(&Server::handleClient, this, clientSocket, clientAddress);
            clientThread.detach();
        }
    }

private:
    int serverSocket;
    int serverPort;

    string login(string username, string hashedPassword) {
        ifstream userFile("registeredUsers.txt");
        if (userFile.is_open()) {
            string line;
            while (getline(userFile, line)) {\
                size_t pos = line.find(":");
                if (pos != string::npos) {
                    string storedUsername = line.substr(0, pos);
                    string storedHashedPassword = line.substr(pos + 1);
                    if (username == storedUsername && hashedPassword == storedHashedPassword) {
                        userFile.close();
                        return "true";  
                    }
                }
            }
            userFile.close();
        } else {
            cerr << "Error opening 'registeredUsers.txt' file" << endl;
        }
        return "down";  
    }


    void registerUser(const string& username, const string& hashedPassword) {
        ofstream userFile("registeredUsers.txt", ios::app);
        if (userFile.is_open()) {
            userFile << username << ":" << hashedPassword << endl;
            userFile.close();
            cout << "User registered: " << username << endl;
        } else {
            cerr << "Error opening or creating 'registeredUsers.txt' file" << endl;
        }
    }
    

    void handleClient(int clientSocket, const sockaddr_in& clientAddress) {
    string choice;
    string userName;
    string hashedPassword;
    if (clientSocket < 0) {
        cerr << "Error accepting client connection" << endl;
        return;
    }

    cout << "Client connected from " << inet_ntoa(clientAddress.sin_addr) << ":" << ntohs(clientAddress.sin_port) << endl;

    // Receive "choice" from the client
    char choiceBuffer[64];
    int bytesRead = recv(clientSocket, choiceBuffer, sizeof(choiceBuffer), 0);
    if (bytesRead < 0) {
        cerr << "Error reading 'choice' from client" << endl;
        close(clientSocket);
        return;
    } else if (bytesRead == 0) {
        cout << "Client disconnected" << endl;
        close(clientSocket);
        return;
    }
    choice = choiceBuffer;

    // Receive "userName" from the client
    char userNameBuffer[128];
    bytesRead = recv(clientSocket, userNameBuffer, sizeof(userNameBuffer), 0);
    if (bytesRead < 0) {
        cerr << "Error reading 'userName' from client" << endl;
        close(clientSocket);
        return;
    } else if (bytesRead == 0) {
        cout << "Client disconnected" << endl;
        close(clientSocket);
        return;
    }
    userName = userNameBuffer;

    // Receive "hashedPassword" from the client
    char hashedPasswordBuffer[512];
    bytesRead = recv(clientSocket, hashedPasswordBuffer, sizeof(hashedPasswordBuffer), 0);
    if (bytesRead < 0) {
        cerr << "Error reading 'hashedPassword' from client" << endl;
        close(clientSocket);
        return;
    } else if (bytesRead == 0) {
        cout << "Client disconnected" << endl;
        close(clientSocket);
        return;
    }
    hashedPassword = hashedPasswordBuffer;
    string response = "down";
    if (choice == "register") {
        registerUser(userName, hashedPassword);
        response = "true";
    } else if(choice == "login") {
        response = login(userName, hashedPassword);
    }

    if (send(clientSocket, response.c_str(), response.length(), 0) < 0) {
        cerr << "Error sending response to client" << endl;
    }

    // Closing the connection 
    close(clientSocket);
}

};

int main() {
    Server server(12345);
    server.start();
    return 0;
}
