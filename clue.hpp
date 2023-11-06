#ifndef CLUES_HPP
#define CLUES_HPP

#include <string>

// CLUE CLASS
class Clue {
public:
    std::string word;       // Word to be found
    std::string clue;       // Clue given to the user
    unsigned int x;        // Starting x position
    unsigned int y;        // Starting y position
    char direction;         // Orientation
    int f;                 // Checks if found
};

#endif
