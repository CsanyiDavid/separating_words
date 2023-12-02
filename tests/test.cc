#define CATCH_CONFIG_MAIN

#include<vector>

#include "catch.hpp"
#include "../automata_gen.h"

TEST_CASE("run automata"){
    std::vector<int> t{1, 3, 1, 2, 5, 2, 6, 4, 1, 0, 6, 4, 2, 6};
    Automata a{t};
    REQUIRE(a.run("") == 0);
    REQUIRE(a.run("000000000000000000000000000") == 1);
    REQUIRE(a.run("110010110011001101") == 2);
    REQUIRE(a.run("011010010111") == 3);

    REQUIRE_THROWS(a.run("011*010010111"));
    REQUIRE_THROWS(a.run("2010010111"));
}
