#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Function to check if a user with the given username and password exists
bool doesUserExist(const std::string& username, const std::string& password, const std::vector<std::string>& users) {
    for (const std::string& user : users) {
        if (user == username + ":" + password) {
            return true;
        }
    }
    return false;
}

// Function to register a new user
void registerUser(std::vector<std::string>& users) {
    std::string username, password;
    std::cout << "Enter a username: ";
    std::cin >> username;
    std::cout << "Enter a password: ";
    std::cin >> password;

    // Add the new user to the vector of users
    users.push_back(username + ":" + password);

    // Save the updated user data to a file
    std::ofstream file("user_data.txt");
    if (file.is_open()) {
        for (const std::string& user : users) {
            file << user << "\n";
        }
        file.close();
        std::cout << "Registration successful.\n";
    } else {
        std::cerr << "Error: Could not save user data.\n";
    }
}

// Function to display the crossword board
void displayCrosswordBoard() {
    // Implement your crossword board display logic here
    std::cout << "Crossword Board:\n";
    // Display the crossword grid
    // Example:
    std::cout << "  A B C D E\n";
    std::cout << "1 # # # # #\n";
    std::cout << "2 # # # # #\n";
    std::cout << "3 # # # # #\n";
    std::cout << "4 # # # # #\n";
    std::cout << "5 # # # # #\n";
}

// Function to display across clues
void displayAcrossClues() {
    // Implement your across clues display logic here
    std::cout << "Across Clues:\n";
    // Example:
    std::cout << "1. A type of fruit (5 letters)\n";
    std::cout << "2. An animal that barks (4 letters)\n";
}

// Function to display vertical clues
void displayVerticalClues() {
    // Implement your vertical clues display logic here
    std::cout << "Vertical Clues:\n";
    // Example:
    std::cout << "1. A color of the rainbow (7 letters)\n";
    std::cout << "2. A flying insect (6 letters)\n";
}

int main() {
    std::vector<std::string> users;

    // Load user data from a file
    std::ifstream file("user_data.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            users.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "Error: Could not load user data.\n";
    }

    while (true) {
        std::cout << "Welcome to the Puzzle Game!\n";
        std::cout << "1. Log In\n";
        std::cout << "2. Register\n";
        std::cout << "3. Quit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string username, password;
            std::cout << "Enter your username: ";
            std::cin >> username;
            std::cout << "Enter your password: ";
            std::cin >> password;

            if (doesUserExist(username, password, users)) {
                std::cout << "Login successful. You are now in the game!\n";
                displayCrosswordBoard();
                displayAcrossClues();
                displayVerticalClues();
                break;
            } else {
                std::cout << "Login failed. Incorrect username or password.\n";
            }
        } else if (choice == 2) {
            registerUser(users);
        } else if (choice == 3) {
            std::cout << "Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}