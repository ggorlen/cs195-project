#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../../src/sokoban.hpp"

TEST_CASE("Default board should be the first board in levels") {
    Sokoban s1 = Sokoban();
    Sokoban s2 = Sokoban(levels[0]);
    
    CHECK(s1.board() == s2.board());
};

TEST_CASE("Two boards should not be the same") {
    Sokoban s1 = Sokoban(2);
    Sokoban s2 = Sokoban(levels[0]);
    CHECK(s1.board() != s2.board());
};