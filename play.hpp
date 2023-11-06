#ifndef PLAY_HPP
#define PLAY_HPP

#include "clue.hpp"
#include <vector>
#include <string>

using namespace std;

int find_index(int a[], int num_elements, int value);

void play(vector<vector<string>> &board, int words, vector<Clue>& clues, int x, int y, int gameOver);

#endif // PLAY_HPP
