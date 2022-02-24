#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../../src/sokoban.hpp"

TEST_CASE("returns the board") {
    std::vector<std::string> level = {
        "#####",
        "#@$.#",
        "#####"
    };
    Sokoban soko = Sokoban();
    
    CHECK(soko.board() == level);
};

TEST_CASE("returns the position of PLAYER") {
    std::vector<std::string> level = {
        "#####",
        "#@$.#",
        "#####"
    };
    Sokoban soko = Sokoban();
    Point test = soko.position(PLAYER);
    Point expected = Point(1, 1);

    CHECK(test.equal(expected));
}

TEST_CASE("returns the position of PLAYER_ON_GOAL") {
    std::vector<std::string> level = {
        "#####",
        "#+$ #",
        "#####",
    };

    Sokoban soko = Sokoban(2);
    Point test = soko.position(PLAYER_ON_GOAL);
    Point expected = Point(1, 1);

    CHECK(test.equal(expected));
}

TEST_CASE("returns an out-of-bound position when player does not exist") {
    std::vector<std::string> level = {
        "####"
    };

    Sokoban soko = Sokoban(3);
    Point test = soko.position(PLAYER_ON_GOAL);
    Point expected = Point(50, 50);

    CHECK(test.equal(expected));
}
// TEST_CASE("change_level throws when the level is out of bounds") {
//     const std::vector<std::string> level{}; 
//     Sokoban soko = Sokoban(); 
    
//     CHECK_THROWS_AS(soko.change_level(1), const std::exception&); }
// };

// TEST_CASE("pushes a box right onto a goal square") {
//     std::vector<std::string> level = {
//         "#####",
//         "#@$.#",
//         "#####"
//     };

//     std::vector<std::string> expected = {
//         "#####",
//         "# @*#",
//         "#####",
//     };
//     Sokoban soko = Sokoban(2);
//     soko.move(Sokoban::Direction::R);
//     CHECK(soko.board() == expected);
// };