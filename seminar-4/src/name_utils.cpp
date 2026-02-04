#include "../inc/name_utils.h"

#include <algorithm>
#include <iostream>
#include <limits>

namespace
{

// Helper Kadane that also returns the start and end indices of the best segment.
std::tuple<int, int, int> maxSubarraySumWithBounds(const std::vector<int>& row)
{
    if (row.empty())
    {
        return std::make_tuple(0, -1, 0);
    }

    int currentSum = row[0];
    int bestSum    = row[0];
    int start      = 0;
    int bestStart  = 0;
    int bestEnd    = 0;

    for (std::size_t i = 1; i < row.size(); ++i)
    {
        if (currentSum < 0)
        {
            currentSum = row[i];
            start      = static_cast<int>(i);
        }
        else
        {
            currentSum += row[i];
        }

        if (currentSum > bestSum)
        {
            bestSum   = currentSum;
            bestStart = start;
            bestEnd   = static_cast<int>(i);
        }
    }

    return std::make_tuple(bestSum, bestStart, bestEnd);
}

}  // namespace

std::vector<std::vector<int>> readMatrix()
{
    int rows = 0;
    int cols = 0;

    if (!(std::cin >> rows >> cols) || rows <= 0 || cols <= 0)
    {
        throw std::runtime_error("Invalid matrix dimensions.");
    }

    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols, 0));
    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            if (!(std::cin >> matrix[r][c]))
            {
                throw std::runtime_error("Failed to read matrix element.");
            }
        }
    }

    return matrix;
}

int maxSubarraySum(const std::vector<int>& row)
{
    if (row.empty())
    {
        return 0;
    }

    int currentSum = row[0];
    int bestSum    = row[0];

    for (std::size_t i = 1; i < row.size(); ++i)
    {
        currentSum = std::max(row[i], currentSum + row[i]);
        bestSum    = std::max(bestSum, currentSum);
    }

    return bestSum;
}

std::tuple<int, int, int, int, int> maxSumSubmatrix(const std::vector<std::vector<int>>& matrix)
{
    if (matrix.empty() || matrix.front().empty())
    {
        throw std::runtime_error("Matrix must not be empty.");
    }

    const int rowCount = static_cast<int>(matrix.size());
    const int colCount = static_cast<int>(matrix.front().size());

    int bestSum = std::numeric_limits<int>::min();
    int bestR1  = 0;
    int bestC1  = 0;
    int bestR2  = 0;
    int bestC2  = 0;

    std::vector<int> temp(rowCount, 0);

    for (int left = 0; left < colCount; ++left)
    {
        std::fill(temp.begin(), temp.end(), 0);

        for (int right = left; right < colCount; ++right)
        {
            for (int rowIndex = 0; rowIndex < rowCount; ++rowIndex)
            {
                temp[rowIndex] += matrix[rowIndex][right];
            }

            const auto [currentSum, top, bottom] = maxSubarraySumWithBounds(temp);

            if (currentSum > bestSum)
            {
                bestSum = currentSum;
                bestR1  = top;
                bestR2  = bottom;
                bestC1  = left;
                bestC2  = right;
            }
        }
    }

    return std::make_tuple(bestR1, bestC1, bestR2, bestC2, bestSum);
}

void printSubmatrix(const std::vector<std::vector<int>>& matrix, int rowBegin, int colBegin, int rowEnd,
                    int colEnd)
{
    for (int rowIndex = rowBegin; rowIndex <= rowEnd; ++rowIndex)
    {
        for (int colIndex = colBegin; colIndex <= colEnd; ++colIndex)
        {
            std::cout << matrix[rowIndex][colIndex] << ' ';
        }
        std::cout << '\n';
    }
}
