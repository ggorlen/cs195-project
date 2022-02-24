#ifndef __ELEMENTS_HPP__
#define __ELEMENTS_HPP__

#include <string>
#include <vector>

/* CELL STATES */ 
const char EMPTY = ' ';
const char WALL = '#';
const char GOAL = '.';
const char BOX = '$';
const char BOX_ON_GOAL = '*';
const char PLAYER = '@';
const char PLAYER_ON_GOAL = '+';

/* MAXIMUM BOARD DIMENSION */
const int LENGTH = 50;
const int WIDTH = 50;

/* Mock level used for testing purposes only */
const std::vector<std::vector<std::string>> levels = {
    {
        "#####",
        "#@$.#",
        "#####"
    },

    {
        "#####",
        "#+$ #",
        "#####"
    },

    {
        "####"
    },

    // Level 4: Use for testing empty_or_goal()
    {
        "#####",
        "#@ $#",
        "#####"
    },

    // Level 5: Use for testing empty_or_goal()
    {
        "#####",
        "#@.$#",
        "#####"
    },

    // Level 6: Use for testing box_or_goal()
    {
        "#####",
        "#+$.#",
        "#####"
    },

    // Level 7: Use for testing box_or_goal()
    {
        "#####",
        "#+* #",
        "#####"
    },

    // Level 8: Use for testing player offset_in_dir
    {
        "#######",
        "#  A  #",
        "#  U  #",
        "#CL@RB#",
        "#  D  #",
        "#  E  #",
        "#######"
    },

    // Level 9: Use for testing player offset_in_dir
    {
        "#######",
        "#  A  #",
        "#  U  #",
        "#CL+RB#",
        "#  D  #",
        "#  E  #",
        "#######"
    },

    {
        "     ###     ",
        "     #@#     ",
        "######$######",
        "#     .     #",
        "#############"
    }
};
#endif
