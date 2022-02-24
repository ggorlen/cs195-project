#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../../src/sokoban.hpp"

/* For test purposes, LEVELS exist on elements.hpp */

TEST_CASE("returns the board") {
    std::vector<std::string> level = {
        "#####",
        "#@$.#",
        "#####"
    };
    Sokoban soko = Sokoban();
    
    CHECK(soko.board() == level);
};

TEST_CASE("change_level throws when the level is out of bounds") {
    Sokoban soko = Sokoban(); 
    CHECK_THROWS_AS(soko.change_level(100), const std::exception&);
};

TEST_CASE("returns the position of PLAYER") {
    Sokoban soko = Sokoban();
    Point test = soko.position(PLAYER);
    Point expected = Point(1, 1);

    CHECK(test.equal(expected));
}

TEST_CASE("returns the position of PLAYER_ON_GOAL") {
    Sokoban soko = Sokoban(2);
    Point test = soko.position(PLAYER_ON_GOAL);
    Point expected = Point(1, 1);

    CHECK(test.equal(expected));
}

TEST_CASE("returns an out-of-bound position when player does not exist") {
    Sokoban soko = Sokoban(3);
    Point test = soko.position(PLAYER_ON_GOAL);
    Point expected = Point(50, 50);

    CHECK(test.equal(expected));
}

TEST_CASE("returns true if the cell at point(x, y) is empty") {
    Sokoban soko = Sokoban(4);

    CHECK(soko.empty_or_goal(Point(1, 2)));
}

TEST_CASE("returns true if the cell at point(x, y) is goal") {
    Sokoban soko = Sokoban(5);

    CHECK(soko.empty_or_goal(Point(1, 2)));
}

TEST_CASE("returns true if the cell at point(x, y) is neither empty nor goal") {
    Sokoban soko = Sokoban(5);

    REQUIRE_FALSE(soko.empty_or_goal(Point(1, 3)));
}

TEST_CASE("returns true if the cell at point(x, y) is box") {
    Sokoban soko = Sokoban(6);

    CHECK(soko.box_or_goal(Point(1, 2)));
}

TEST_CASE("returns true if the cell at point(x, y) is box_on_goal") {
    Sokoban soko = Sokoban(7);

    CHECK(soko.box_or_goal(Point(1, 2)));
}

TEST_CASE("returns true if the cell at point(x, y) is neither box nor box_on_goal") {
    Sokoban soko = Sokoban(7);

    REQUIRE_FALSE(soko.box_or_goal(Point(1, 3)));
}


TEST_CASE("returns offset in the direction given.") {
    Sokoban soko = Sokoban(8);
    Point player = soko.position(PLAYER);
    Point offset = soko.offset_in_dir(Sokoban::Direction::U, player, 1);
    CHECK(soko.item(offset) == 'U');

    offset = soko.offset_in_dir(Sokoban::Direction::D, player, 1);
    CHECK(soko.item(offset) == 'D');

    offset = soko.offset_in_dir(Sokoban::Direction::L, player, 2);
    CHECK(soko.item(offset) == 'C');

    soko = Sokoban(9);
    player = soko.position(PLAYER_ON_GOAL);
    offset = soko.offset_in_dir(Sokoban::Direction::U, player, 1);
    CHECK(soko.item(offset) == 'U');
}


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