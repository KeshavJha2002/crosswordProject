#include <iostream>
#include <string>
#include <fstream>
#include "showf.hpp"
#include "updatef.hpp"
#include "clue.hpp"
#include "createArray.hpp"
#include "readTF.hpp"
#include "play.hpp"
#include <map>

using namespace std;

int main() {
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
    cout << "Enter the number of CrossBoard You want to play with : ";

    int boardChoice;
    if (!(cin >> boardChoice)) {
        cerr << "Invalid input. Please enter a number." << endl;
        return 1;
    }

    // Clear the input buffer?
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
            cerr << "Invalid choice. Using default board." << endl;
            filename = "cw.txt";
            break;
    }

    crossword.open(filename);
    if (!crossword.is_open()) {
        cerr << "Error opening game board file: " << filename << endl;
        return 1;
    }

    cout << "Loading game board..." << endl;
    crossword >> x >> y >> words;
    cout << "Game is " << x << " rows x " << y << " cols with " << words << " words" << endl;
    clues = readTF(crossword, words);
    crossword.close();

    board = createArray(x, y);
    play(board, words, clues, x, y, gameOver);

    return 0;
}
