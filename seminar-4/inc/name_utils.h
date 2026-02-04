#pragma once

#include <tuple>
#include <vector>

// Reads a matrix of integers from standard input.
// The first line should contain two integers: number of rows and columns.
// The following lines contain the matrix elements row by row.
std::vector<std::vector<int>> readMatrix();

// One-dimensional Kadane algorithm:
// returns the maximum sum of a contiguous subarray in the given row.
int maxSubarraySum(const std::vector<int>& row);

// Two-dimensional Kadane reduction:
// returns a tuple (r1, c1, r2, c2, sum) where
// (r1, c1) is the top-left and (r2, c2) is the bottom-right corner
// of the submatrix with maximum sum, and sum is this maximum sum.
std::tuple<int, int, int, int, int> maxSumSubmatrix(const std::vector<std::vector<int>>& matrix);

// Prints the submatrix [rowBegin..rowEnd] x [colBegin..colEnd] (inclusive) to standard output.
void printSubmatrix(const std::vector<std::vector<int>>& matrix, int rowBegin, int colBegin, int rowEnd,
                    int colEnd);
