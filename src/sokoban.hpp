#ifndef __SOKOBAN_HPP__
#define __SOKOBAN_HPP__
#include <vector>
#include <string>
#include "elements.hpp"

class Sokoban {
    /* Sokoban Attribute */
    protected:
        std::vector<std::string> current_board;
        std::string movesSequence;
        unsigned int current_level;
        unsigned int moves_count;

    /* Sokoban Methods */
    public:
        Sokoban();
        Sokoban(unsigned int inputNumber);
        std::vector<std::string> getWorld();
        bool move(Direction direction);
        void change_level(unsigned int level_number);
        void set_level(unsigned int level_number);
        void reset();
        void undo();
        std::vector<std::string> board();
        unsigned int moves();
        unsigned int level();
        bool solved();
};
#endif