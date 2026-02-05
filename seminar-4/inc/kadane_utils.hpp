#pragma once

#include <cstdint>
#include <tuple>
#include <vector>

namespace kadane
{

std::vector<std::vector<int>> readMatrix();
std::tuple<int, int, int64_t> maxSubarraySum(const std::vector<int>& row);
std::tuple<int, int, int, int, int64_t> maxSumSubmatrix(const std::vector<std::vector<int>>& matrix);
void printSubmatrix(const std::vector<std::vector<int>>& matrix, int rowUpperLeft, int columnUpperLeft,
                    int rowLowerRight, int columnLowerRight);

}  // namespace kadane