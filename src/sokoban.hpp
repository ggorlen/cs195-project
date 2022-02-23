#ifndef __SOKOBAN_HPP__
#define __SOKOBAN_HPP__

#include <string>
#include <vector>

#include "elements.hpp"

class Sokoban {
    protected:
        std::vector<std::string> current_board;
        std::string moves;
        unsigned int current_level;
    public:
        enum Direction {U, D, L, R};

        Sokoban();
        Sokoban(unsigned int level);
        void change_level(unsigned int level_number);
        void reset();
        bool undo();
        std::vector<std::string> board();
        bool move(Direction direction);
        unsigned int moves_count();
        unsigned int level();
        bool solved();
        void print();
};
#endif