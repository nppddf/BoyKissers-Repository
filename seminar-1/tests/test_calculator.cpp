#include <catch2/catch_test_macros.hpp>
#include "plus.h"

TEST_CASE("sum of positive numbers") {
    REQUIRE(sum(5, 47) == 52);
    REQUIRE(sum(1, 2) == 3);
    REQUIRE(sum(10, 20) == 30);
    REQUIRE(sum(24082007, 16032007) == 40114014);
}

TEST_CASE("sum with zero") {
    REQUIRE(sum(0, 0) == 0);
    REQUIRE(sum(0, 5) == 5);
    REQUIRE(sum(7, 0) == 7);
}

TEST_CASE("sum with negative numbers") {
    REQUIRE(sum(-1, -2) == -3);
    REQUIRE(sum(-5, 5) == 0);
    REQUIRE(sum(-10, 3) == -7);
}

TEST_CASE("sum with negative and positive numbers") {
    REQUIRE(sum(3, 7) == sum(7, 3));
    REQUIRE(sum(-4, 9) == sum(9, -4));
}
