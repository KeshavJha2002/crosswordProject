#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "clue.hpp"
#include "updatef.hpp"
#include "showf.hpp"

using namespace std;

int find_index(int a[], int num_elements, int value) {
    int i;
    for (i = 0; i < num_elements; i++) {
        if (a[i] == value) {
            return 1;
        }
    }
    return 0;
}

void play(vector< vector<string>>& board, int words, vector<Clue>& clues, int x, int y, int gameOver) {
    string answer;
    int solve;
    int i;
    vector<int> checkFound(words, 0);
    vector<int> wasFound(words, 0);
    string direction;
    for (i = 0; i < words; i++) {
        checkFound[i] = i + 1;
        wasFound[i] = 0;
    }
    for (i = 0; i < words; i++) {
        board = updatef(board, clues, i);
    }
    showf(x, y, board);
    do {
        cout << "\t";
        for (i = 0; i < y; i++)
            cout << "***";
        int j;
        cout << "\nClues: \n";
        cout << "#  Direction  \t row  col   Hint\n";
        cout << "---------------------------------\n";
        for (j = 0; j < words; j++) {
    if (clues[j].direction == 'H') {
        direction = "Horizontal";
    } else if (clues[j].direction == 'V') {
        direction = "Vertical";
    }
    
    // Check if the clue has been solved (wasFound[solve - 1] == 0)
    if (wasFound[j] == 0) {
        cout << j + 1 << ": " << direction << "\t  " << clues[j].x;
        cout << "   " << clues[j].y << "   " << clues[j].clue << endl;
    }
}
        cout << "\n";
        do {
            cout << "Enter -1 to exit\n";
            cout << "Which clue do you want to solve?: ";
            if (!(cin >> solve) || solve < 1) {
                solve = 0;
            }
            if (solve == -1) {
                return;
            }
            if (wasFound[solve - 1] == 1) {
                cout << "That clue has been solved\n";
                solve = 0;
            }
            else if (checkFound[solve - 1] == 0) {
                cout << "That clue is invalid\n";
                solve = 0;
            }
        } while (solve < 1 || solve > words);
        cout << "Current hint: " << clues[solve - 1].clue << endl;
        cout << "Enter your solution: ";
        cin >> answer;
        for (i = 0; i < answer.length(); i++) {
            answer[i] = toupper(answer[i]);
        }
        if (answer != clues[solve - 1].word) {
            cout << "WRONG ANSWER\n";
            showf(x, y, board);
        }
        else {
            cout << "\nCorrect!\n\n";
            clues[solve - 1].f = 1;
            wasFound[solve - 1] = solve;
            checkFound[solve - 1] = 0;
            board = updatef(board, clues, solve - 1);
            showf(x, y, board);
            gameOver++;
        }
    } while (gameOver != words);
    cout << "\nYou beat the crossword puzzle! Congratulations!\n\n";
}
