#ifndef __SOKOBAN_HPP__
#define __SOKOBAN_HPP__
#include <vector>
#include <string>
#include "elements.hpp"

class Sokoban {

protected:
    std::vector<std::string> world;

public:
    Sokoban();
    Sokoban(int inputNumber);
    std::vector<std::string> getWorld();
    std::vector<std::string> level(int inputNumber);
    void printMap();
};
#endif