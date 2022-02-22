#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "sokoban.hpp"

/* Constructor with default level 1*/
Sokoban::Sokoban() {
    Sokoban(1);
}

/* Constructor with a specified level number*/
Sokoban::Sokoban(unsigned int level) {
    change_level(level);
}

/* Switch to a specific level */
void Sokoban::change_level(unsigned int level) {
    if (level > levels.size()) {
        throw std::invalid_argument("Level does not exist.");
    } 

    current_level = level;
    current_board = levels[current_level - 1];
}

/* Reset the current level to its original state */
void Sokoban::reset() {
    change_level(current_level);
}

/* Undo the last move if MOVES is not an empty string */
void Sokoban::undo() {
    if (!moves.empty()) {
        moves.pop_back();
    }
}


/* Attempt a player move in direction (up/down/left/right) 
 * and return true/false to indicate if it was successful.
 */

/**** TO BE IMPLEMENTED *****/
bool Sokoban::move(Direction direction) {

    return false;
}

/* Return the current baord */
std::vector<std::string> Sokoban::board() {
    return current_board;
}

/* Return the number of moves made on the current board */
unsigned int Sokoban::moves_count() {
    return moves.size();
}

/* Return the current level number */
unsigned int Sokoban::level() {
    return current_level;
}

/* Return whether the current board is solved */
bool Sokoban::solved() {
    
    for (auto row : current_board) {
        /* When GOAL is found, this means that
         * a box is not yet placed in the goal */
        if (row.find(GOAL) < row.size()) {
            return false;
        }
    }
    return true;
}

/*
 *  UTILITY FUNCTION
 */

void print(std::vector<std::string> board) {
    for (std::string row : board) {
        std::cout << row << std::endl;
    }
}

int main() {
    Sokoban soko = Sokoban();
    print(soko.board());

    soko = Sokoban(1);
    print(soko.board());
    return 0;
}
