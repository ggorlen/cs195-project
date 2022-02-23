#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "sokoban.hpp"

/* Constructor with default level 1*/
Sokoban::Sokoban() {
    change_level(1);
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
bool Sokoban::undo() {
    if (!moves.empty()) {
        moves.pop_back();
        return true;
    }
    return false;
}

/* Return the current baord */
std::vector<std::string> Sokoban::board() {
    return current_board;
}

/* Attempt a player move in direction (up/down/left/right) 
 * and return true/false to indicate if it was successful.
 */
/**** TO BE IMPLEMENTED *****/
bool Sokoban::move(Direction direction) {
    // find the location of the character (@) on the current board
    // get possible cell to move into, findPossibleMove
        // return a list of coordinate to move to, if not possible coord will be a tuple of infinity

    // append direction to MOVES
    return false;
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
        /* When GOAL or PLAYER_ON_GOAL is found, this means that
         * a box is not yet placed in the goal */
        if (   row.find(GOAL) < row.size() 
            || row.find(PLAYER_ON_GOAL) < row.size()) {
            return false;
        }
    }
    return true;
}

void Sokoban::print() {
    for (auto& row : current_board) {
        std::cout << row << std::endl;
    }
}


// int main() {
//     Sokoban soko = Sokoban();
//     soko.print();

//     soko = Sokoban(5);
//     soko.print();
//     return 0;
// }
