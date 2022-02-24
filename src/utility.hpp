#ifndef __UTILITY_CPP__
#define __UTILITY_CPP__

#include <iostream>
#include <string>
#include <vector>
#include "point.hpp"

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

void print(char chr) {
    std::cout << chr << std::endl;
}

void print(Point p) {
    std::cout << '(' << p.x << ',' << p.y << ')' << std::endl;
}
#endif