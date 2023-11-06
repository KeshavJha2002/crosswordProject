#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clue.hpp"

using namespace std;

vector<Clue> readTF(ifstream& inputFile, int Words) {
    vector<Clue> Clues(Words);
    for (int i = 0; i < Words; i++) {
        inputFile >> Clues[i].direction >> Clues[i].x >> Clues[i].y;
        inputFile.ignore(); 
        string line;
        getline(inputFile, line);
        size_t spacePos = line.find(' ');
        Clues[i].word = line.substr(0, spacePos);
        Clues[i].clue = line.substr(spacePos + 1);
    }

    return Clues;
}
