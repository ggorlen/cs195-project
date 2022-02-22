#include <exception>
#include <iostream>
#include <vector>
#include <string>
#include "sokoban.hpp"

/* Constructor with default level 1*/
Sokoban::Sokoban() {
    Sokoban(1);
}

/* Constructor with a specified level number*/
Sokoban::Sokoban(unsigned int level) {
    change_level(inputNumber);
}

/* Switch to level level_number*/
void Sokoban::change_level(unsigned int level_number) {
    if (level_number > levels.size()) {
        throw std::invalid_argument("Level does not exist.");
    } else {
        current_level = level_number;
        current_board = levels[current_level - 1];
    }
}

/* Reset the current level to its original state */
void Sokoban::reset() {
    change_level(current_level);
}

/* Undo the last move */
void Sokoban::undo() {
    moves.pop_back();
}

/* Return the current baord */
std::vector<std::string> Sokoban::board() {
    return current_board;
}

/* Return the number of moves made on the current board */
unsigned int Sokoban::moves () {
    return moves_count;
}

/* Return the current level number */
unsigned int Sokoban::level() {
    return current_level;
}

/* Return whether the current board is solved */
bool Sokoban::solved() {
    
    for (std::string row : current_board) {
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

    soko = Sokoban(5);
    print(soko.board());
    return 0;
}
