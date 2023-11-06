#include <iostream>
#include <vector>

using namespace std;

void showf(int rows, int cols, const vector<vector<string>>& board) {
    cout << "Current puzzle:\n\n";
    cout << "\t";
    for (int i = 0; i < cols; i++) {
        if (i < 9) {
            cout << "  " << i + 1;
        } else {
            cout << " " << i + 1;
        }
    }
    cout << "\n\t  ";
    for (int i = 0; i < cols; i++) {
        cout << " " << '-' << ' ' << '-';
    }
    cout << "\n";
    for (int i = 0; i < rows; i++) {
        cout << i + 1 << "\t| ";
        for (int j = 0; j < cols; j++) {
            cout << board[i][j] << "  ";
        }
        cout << endl;
    }
}
