#include <iostream>
#include <vector>
#include <string>
#include "sokoban.hpp"

/* Constructor with default level 1*/
Sokoban::Sokoban() {
    world = level(1);
}

/* Constructor with a specified level number*/
Sokoban::Sokoban(int inputNumber) {
    world = level(inputNumber);
};

/* UTILITY FUNCTIONS */
std::vector<std::string> Sokoban::level(int inputNumber) {
    return worlds[inputNumber - 1];
};

void Sokoban::printMap() {
    for(std::string line : world) {
        std::cout << line << std::endl;
    }    
};

int main() {
    Sokoban soko = Sokoban();
    soko.printMap();
}
