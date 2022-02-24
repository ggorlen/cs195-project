#ifndef __SOKOBAN_HPP__
#define __SOKOBAN_HPP__

#include <string>
#include <vector>
#include "elements.hpp"
#include "point.hpp"

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

    /* Utility Functions */
    Point position(const char item);
    char to_char(Direction direction);
    bool empty_or_goal(int x, int y);
    bool box_or_goal(int x, int y);
    bool make_move(Direction direction, Point origin);
    void set(Direction direction, Point point);
    Point offset_in_dir(Direction direction, Point point, int offset);
    const char replace(const char player);
};
#endif