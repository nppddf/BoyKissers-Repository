#include <catch2/catch_test_macros.hpp>

#include "../inc/kadane_utils.hpp"

TEST_CASE("maxSumSubmatrix finds the best submatrix in a mixed matrix")
{
    std::vector<std::vector<int>> matrix = {
        {1, 2, -1, -4, -20},
        {-8, -3, 4, 2, 1},
        {3, 8, 10, 1, 3},
        {-4, -1, 1, 7, -6},
    };

    auto [topRow, leftCol, bottomRow, rightCol, bestSum] =
        kadane::maxSumSubmatrix(matrix);

    REQUIRE(bestSum == 29);
    REQUIRE(topRow == 1);
    REQUIRE(leftCol == 1);
    REQUIRE(bottomRow == 3);
    REQUIRE(rightCol == 3);
}

TEST_CASE("maxSumSubmatrix handles all-negative matrices")
{
    std::vector<std::vector<int>> matrix = {
        {-1, -2},
        {-3, -4},
    };

    auto [topRow, leftCol, bottomRow, rightCol, bestSum] =
        kadane::maxSumSubmatrix(matrix);

    REQUIRE(bestSum == -1);
    REQUIRE(topRow == 0);
    REQUIRE(leftCol == 0);
    REQUIRE(bottomRow == 0);
    REQUIRE(rightCol == 0);
}

TEST_CASE("maxSumSubmatrix rejects empty matrices")
{
    std::vector<std::vector<int>> matrix;
    REQUIRE_THROWS_AS(kadane::maxSumSubmatrix(matrix), std::invalid_argument);
}