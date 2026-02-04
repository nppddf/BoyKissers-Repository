#include <catch2/catch_test_macros.hpp>
#include <tuple>
#include <vector>

#include "name_utils.h"

TEST_CASE("maxSubarraySum handles mixed positive and negative values")
{
    const std::vector<int> row{1, -2, 3, 4, -1};
    const int result = maxSubarraySum(row);
    REQUIRE(result == 7);  // 3 + 4
}

TEST_CASE("maxSubarraySum handles all negative values")
{
    const std::vector<int> row{-5, -1, -7};
    const int result = maxSubarraySum(row);
    REQUIRE(result == -1);  // maximum element
}

TEST_CASE("maxSumSubmatrix finds correct submatrix in mixed matrix")
{
    const std::vector<std::vector<int>> matrix{
            {1, 2, -1, -4},
            {-8, 3, 4, 2},
            {3, 8, 10, -8},
    };

    const auto [rowBegin, colBegin, rowEnd, colEnd, bestSum] = maxSumSubmatrix(matrix);

    REQUIRE(bestSum == 26);
    REQUIRE(rowBegin == 0);
    REQUIRE(colBegin == 1);
    REQUIRE(rowEnd == 2);
    REQUIRE(colEnd == 2);
}

TEST_CASE("maxSumSubmatrix handles matrix of all negative numbers")
{
    const std::vector<std::vector<int>> matrix{
            {-3, -4},
            {-1, -2},
    };

    const auto [rowBegin, colBegin, rowEnd, colEnd, bestSum] = maxSumSubmatrix(matrix);

    REQUIRE(bestSum == -1);
    REQUIRE(rowBegin == 1);
    REQUIRE(colBegin == 0);
    REQUIRE(rowEnd == 1);
    REQUIRE(colEnd == 0);
}
