#include "sokoban.hpp"

#include <iostream>
#include <queue>
#include <stack>
#include <stdexcept>
#include <unordered_map>

#include "print.cpp" // DELETE

Sokoban::Sokoban(std::vector<std::vector<std::string>> levels) {
    this->levels = levels;
    change_level(0);
}

void Sokoban::print_board() {
    for (const std::string &row : board()) {
        std::cout << row << '\n';
    }
}

unsigned int Sokoban::level() {
    return current_level;
}

bool Sokoban::solved() {
    for (const std::string &row : board()) {
        for (const char cell : row) {
            if (cell == Cell::GOAL ||
                cell == Cell::PLAYER_ON_GOAL) {
                return false;
            }
        }
    }
    return true;
}

std::vector<std::string> Sokoban::board() {
    return _board;
}

void Sokoban::locate_player() {
    for (unsigned int y = 0; y < _board.size(); y++) {
        for (unsigned int x = 0; x < _board[y].size(); x++) {
            if (_board[y][x] == Cell::PLAYER ||
                _board[y][x] == Cell::PLAYER_ON_GOAL) {
                px = x;
                py = y;
                return;
            }
        }
    }
    throw std::invalid_argument("Player not found...");
}

void Sokoban::move_player(int dy, int dx) {
    // Set the cell state when player leaves the current cell
    _board[py][px] = (_board[py][px] == Cell::PLAYER_ON_GOAL) ? 
        Cell::GOAL : Cell::EMPTY;

    // Set the cell state when player arrives to the new cell
    _board[py+dy][px+dx] = (_board[py+dy][px+dx] == Cell::GOAL) ? 
        Cell::PLAYER_ON_GOAL : Cell::PLAYER;
    py += dy;
    px += dx;
}

void Sokoban::push_box(int dy, int dx) {
    // Set the cell state when box leaves the current cell
    _board[py+dy][px+dx] = (_board[py+dy][px+dx] == Cell::BOX_ON_GOAL) ? 
        Cell::GOAL : Cell::EMPTY;

    // Set the cell state when box arrives to the new cell
    _board[py+dy+dy][px+dx+dx] = (_board[py+dy+dy][px+dx+dx] == Cell::GOAL) ? 
        Cell::BOX_ON_GOAL : Cell::BOX;
}

/* Update move with associated board state */
void Sokoban::update(Direction direction, bool fast_forward) {
    moves.push_back(direction);
    history.push_back(std::make_pair(_board, fast_forward));
}

bool Sokoban::make_move(Direction direction, bool fast_forward = false) {
    auto [dy, dx] = dir_offsets.at(direction);

    // Player moves to a goal or empty cell
    if (_board[py+dy][px+dx] == Cell::GOAL || 
        _board[py+dy][px+dx] == Cell::EMPTY) {

        move_player(dy, dx);
        update(direction, fast_forward);

        return true;
    }

    // Player encounters a box or box on goal
    if (_board[py+dy][px+dx] == Cell::BOX ||
        _board[py+dy][px+dx] == Cell::BOX_ON_GOAL) {
        
        // If the cell next to the box is a goal or empty cell,
        // then the player can push box to that cell
        if (_board[py+dy+dy][px+dx+dx] == Cell::EMPTY ||
            _board[py+dy+dy][px+dx+dx] == Cell::GOAL) {

            push_box(dy, dx);
            move_player(dy, dx);
            update(direction, fast_forward);

            return true;
        }
    }
    return false;
}

bool Sokoban::move(Direction direction, bool fast_forward) {
    undone.clear();
    return make_move(direction, fast_forward);
}

bool Sokoban::move(Direction direction) {
    undone.clear();
    return make_move(direction);
}

bool Sokoban::move(unsigned int y, unsigned int x) {

    auto origin = std::make_pair(py, px);
    auto destination = std::make_pair(y, x);

    // If the specified destination is the same, don't do anything
    if (origin == destination) {
        return false;
    }

    // If the specified destination is next to the player,
    // try to move to that destination
    for (const auto &[dir, offset] : dir_offsets) {
        auto delta = std::make_pair(origin.first + offset.first, origin.second + offset.second);
        if (delta == destination) {
            return move(dir);
        }
    }

    std::queue<std::pair<unsigned int, unsigned int>> queue;
    std::unordered_map<std::pair<unsigned int, unsigned int>, 
        std::pair<unsigned int, unsigned int>, PairHash, PairEqual> visited;

    // Add origin to the queue and visited map
    queue.push(origin);
    visited[origin] = std::make_pair(0, 0);

    // Visit all paths to a destination if possible
    while (!queue.empty()) {
        // Get the first path from the queue
        auto current = queue.front();
        queue.pop();

        if (current == destination) {
            // Mark the origin with fast-forward
            history.back().second = true;

            // Build the valid path from the origin to the destination
            std::stack<std::pair<unsigned int, unsigned int>> paths;

            while (!(origin == current)) {
                paths.push(current);
                current = visited[current];
            }

            // Execute move for every path in paths
            while (!paths.empty()) {
                std::pair<int, int> next = paths.top();
                std::pair<int, int> offset(next.first - current.first, next.second - current.second);
                bool moved = false;

                

                for (const auto &[direction, value] : dir_offsets) {
                    if (offset == dir_offsets.at(direction)) {
                        moved = (paths.size() == 1) ? move(direction, true) : move(direction, false);
                    }
                }

                current = next;
                paths.pop();
            }

            // Player has been moved to the destination.
            return true;
        }

        // If destination has not yet been found, get the cardinal adjacent neighbors 
        std::vector<std::pair<unsigned int, unsigned int>> neighbors;
        for (const auto &[key, value] : dir_offsets) {

            auto adj = std::make_pair(current.first + value.first, current.second + value.second);
            
            if (visited.find(adj) == visited.end()) {
                if (_board.at(adj.first).at(adj.second) == Cell::EMPTY || 
                    _board.at(adj.first).at(adj.second) == Cell::GOAL) {
                    neighbors.push_back(adj);
                }
                else if (adj == destination) {
                    neighbors.push_back(adj);
                }
            }

        }

        // Add neighbors to visited with its associated parent, and then enqueue
        for (const auto &neighbor : neighbors) {
            visited[neighbor] = current;
            queue.push(neighbor);
        }
    }
    
    // No valid path to the destination
    return false;
}

bool Sokoban::undo() {
    if (moves.empty()) {
        return false;
    }

    undone.push_back(std::make_pair(moves.back(), _board));

    moves.pop_back();
    history.pop_back();

    _board = history.back().first;
    locate_player();

    return true;
}

bool Sokoban::rewind() {
    
    if (moves.empty()) {
        return false;
    }
    
    undo();

    // Reset fast_forward if the previous state is landmarked as fast_forward
    // bool fast_forward = history.back().second;
    // if (fast_forward) {
    //     history.back().second = false;
    //     return false;
    // }

    while (!history.empty()) {
        bool fast_forward = history.back().second;

        // std::cout << "size: " << history.size();
        // std::cout << "ff: " << fast_forward << std::endl;
        // std::cout << "board: ";
        //print_board();

        if (!fast_forward) {
            undo();
        }
        else {
            history.back().second = false;
            break;
        }
    }

    return true;
}

bool Sokoban::redo() {
    if (undone.empty()) {
        return false;
    }

    Direction direction = undone.back().first;
    _board = undone.back().second;
    update(direction, false);  //TODO

    undone.pop_back();

    locate_player();

    return true;
}

void Sokoban::reset() {
    change_level(current_level);
}

void Sokoban::change_level(unsigned int level_number) {
    current_level = level_number;
    _board = levels.at(current_level);
    moves.clear();
    undone.clear();
    history.push_back(std::make_pair(_board, false));
    locate_player();
}
