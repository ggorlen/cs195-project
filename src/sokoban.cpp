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

/* Return the current board */
std::vector<std::string> Sokoban::board() {
    return current_board;
}

/* Attempt a player move in direction (up/down/left/right) 
 * and return true/false to indicate if it was successful.
 */
/**** TO BE IMPLEMENTED *****/
// bool Sokoban::move(Direction direction) {
//     // find the location of the PLAYER('@') or PLAYER_ON_GOAL ('+') on the current board
//     bool onGoal = false;
//     Point p_pos = position(PLAYER);
//     int row = p_pos.x;
//     int col = p_pos.y;
    
//     if (row > LENGTH && col > WIDTH) {
//         p_pos = position(PLAYER_ON_GOAL);
//         row = p_pos.x;
//         col = p_pos.y; 
//         onGoal = true;
//     }
//     // append direction to MOVES
//     if (make_move(direction, Point(row, col))) {
//         moves.push_back(to_char(direction));
//         return true;
//     }
//     return false;
// }

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
        if ( row.find(GOAL) < row.size() || 
            row.find(PLAYER_ON_GOAL) < row.size()) {

            return false;
        }
    }
    return true;
}

/*
 * UTILITY FUNCTIONS
 */

/* Return the x and y position of an ITEM. If ITEM is not found,
 * it will return a location not on the board.
 */
Point Sokoban::position(const char item) {
    std::vector<std::string> board = current_board;
    for (int row = 0; row < board.size(); row ++ ) {
        for (int col = 0; col < board[row].size(); col++) {
            if (current_board[row][col] == item) {
                    return Point(row, col);
                }
        }
    }
    return Point(LENGTH, WIDTH);
}

/* Convert direction to its equivalent character */
char Sokoban::to_char(Direction direction) {
    if (direction == U) {
        return 'U';
    }
    else if (direction == D) {
        return 'D';
    }
    else if (direction == L) {
        return 'L';
    }
    else if (direction == R) {
        return 'R';
    }
    else {
        return ' ';
    }
}

/* If a cell is a valid move, make_move() will move the player to that cell. */
bool Sokoban::make_move(Direction direction, Point origin) {
    Point next = offset_in_dir(direction, origin, 1);
    Point os_next = offset_in_dir(direction, origin, 2);
    if (empty_or_goal(next.x, next.y) ||
        (box_or_goal(next.x, next.y) && 
        empty_or_goal(os_next.x, os_next.y))) {

        set(direction, origin);
        return true;
    }
    return false;

}

/* Return the point on the board specified by the offset and direction */
Point Sokoban::offset_in_dir(Direction direction, Point p, int offset) {
    if (direction == U) {
        return Point(p.x + offset, p.y);
    }
    else if (direction == D) {
        return Point(p.x - offset, p.y);
    }
    else if (direction == L) {
        return Point(p.x, p.y - offset);
    }
    else if (direction == R) {
        return Point(p.x, p.y + offset);
    }
    else {
        /*********TO DO ********/
        // throw an exception
        return Point(0, 0);
    }
}

/* Return true if the current cell is empty or goal. Otherwise, return false */
bool Sokoban::empty_or_goal(int x, int y) {
    return current_board[x][y] == EMPTY || current_board [x][y] == GOAL;
}

/* Return true if the current cell is a box or box_on_goal. Otherwise, return false */
bool Sokoban::box_or_goal(int x, int y) {
    return current_board[x][y] == BOX || current_board[x][y] == BOX_ON_GOAL;
}

/* Set the element on the board in the specified direction */
void Sokoban::set(Direction direction, Point p) {
    const char current_item = current_board[p.x][p.y];
    Point next = offset_in_dir(direction, p, 1);
    const char next_item = current_board[next.x][next.y];
    Point os_next = offset_in_dir(direction, p, 2);
    const char os_next_item = current_board[os_next.x][os_next.y];

    if (current_item == PLAYER || current_item == PLAYER_ON_GOAL) {
        if (next_item == EMPTY) {
            current_board[p.x][p.y] = replace(current_item);
            current_board[next.x][next.y] = PLAYER; 
        }
        else if (next_item == GOAL) {
            current_board[p.x][p.y] = EMPTY;
            current_board[next.x][next.y] = PLAYER_ON_GOAL;
        }
        else if (next_item == BOX) {
            if (os_next_item == EMPTY) {
                current_board[p.x][p.y] = EMPTY;
                current_board[next.x][next.y] = PLAYER;
                current_board[os_next.x][os_next.y] = BOX;
            }
            else if (os_next_item == GOAL) {
                current_board[p.x][p.y] = EMPTY;
                current_board[next.x][next.y] = PLAYER;
                current_board[os_next.x][os_next.y] = BOX_ON_GOAL;
            }
        }
        else if (next_item == BOX_ON_GOAL) {
            if (os_next_item == EMPTY) {
                current_board[p.x][p.y] = EMPTY;
                current_board[next.x][next.y] = PLAYER_ON_GOAL;
                current_board[os_next.x][os_next.y] = BOX;                
            } 
            else if (os_next_item == GOAL) {
                current_board[p.x][p.y] = EMPTY;
                current_board[next.x][next.y] = PLAYER_ON_GOAL;
                current_board[os_next.x][os_next.y] = BOX_ON_GOAL;
            }
        }
    }
}

const char Sokoban::replace(const char player) {
    if (player == PLAYER) {
        return EMPTY;
    } 
    else if (player == PLAYER_ON_GOAL) {
        return GOAL;
    }
    else {
    /****************TODO ********/
        return '\0';
    }
}

void print(std::vector<std::string> board) {
    for (auto& row : board) {
        std::cout << row << std::endl;
    }
}

void print(int val) {
    std::cout << val << std::endl;
}

void print(std::string str) {
    std::cout << str << std::endl;
}

void print(Point p) {
    std::cout << '(' << p.x << ',' << p.y << ')' << std::endl;
}

int main() {
    Sokoban soko = Sokoban();
    print(soko.board());

    print(soko.position(PLAYER));

    soko = Sokoban(2);
    print(soko.board());
    print(soko.position(PLAYER_ON_GOAL));

    soko = Sokoban(3);
    print(soko.board());
    print(soko.position(PLAYER_ON_GOAL));

    return 0;
}
