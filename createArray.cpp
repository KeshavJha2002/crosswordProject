#include <iostream>
#include <vector>
#include "clue.hpp"

using namespace std;

vector<vector<string>> createArray(int rows, int cols) {
    vector<vector<string>> myArray(rows, vector<string>(cols, "#"));
    return myArray;
}
