#include "../inc/kadane_utils.hpp"

#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <tuple>
#include <vector>

namespace kadane
{

namespace
{

std::tuple<int, int, int64_t> maxSubarraySum(const std::vector<int64_t>& array)
{
    int64_t currentSum     = array[0];
    int64_t currentBestSum = array[0];
    int currentLeftCol     = 0;

    std::tuple<int, int, int64_t> maxSubarray = {0, 0, currentBestSum};
    for (int i = 1; i < static_cast<int>(array.size()); ++i)
    {
        if (currentSum < 0)
        {
            currentSum     = array[i];
            currentLeftCol = i;
        }
        else
        {
            currentSum += array[i];
        }

        if (currentSum >= currentBestSum)
        {
            currentBestSum = currentSum;
            maxSubarray    = std::make_tuple(currentLeftCol, i, currentBestSum);
        }
    }

    return maxSubarray;
}

}  // namespace

std::tuple<int, int, int, int, int64_t> maxSumSubmatrix(const std::vector<std::vector<int>>& matrix)
{
    if (matrix.empty() || matrix[0].empty())
    {
        throw std::invalid_argument("Empty matrix.");
    }

    int width  = static_cast<int>(matrix.size());
    int height = static_cast<int>(matrix[0].size());

    std::vector<std::vector<int64_t>> prefixSum(width + 1, std::vector<int64_t>(height, 0));
    for (int i = 1; i <= width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            prefixSum[i][j] = prefixSum[i - 1][j] + matrix[i - 1][j];
        }
    }

    std::tuple<int, int, int, int, int64_t> maxSumSubmatrix = {-1, -1, -1, -1,
                                                               std::numeric_limits<int64_t>::min()};
    for (int topRow = 0; topRow < width; ++topRow)
    {
        std::vector<int64_t> columnsSum(height);
        for (int bottomRow = topRow; bottomRow < width; ++bottomRow)
        {
            for (int i = 0; i < height; ++i)
            {
                columnsSum[i] = prefixSum[bottomRow + 1][i] - prefixSum[topRow][i];
            }

            auto [leftCol, rightCol, bestSum] = maxSubarraySum(columnsSum);

            if (bestSum > std::get<4>(maxSumSubmatrix))
            {
                maxSumSubmatrix = std::make_tuple(topRow, leftCol, bottomRow, rightCol, bestSum);
            }
        }
    }

    return maxSumSubmatrix;
}

std::vector<std::vector<int>> readMatrix()
{
    int rows = 0;
    int cols = 0;

    if (!(std::cin >> rows >> cols))
    {
        throw std::runtime_error("Failed to read matrix dimensions.");
    }

    if (rows <= 0 || cols <= 0)
    {
        throw std::invalid_argument("Matrix dimensions must be positive.");
    }

    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (!(std::cin >> matrix[i][j]))
            {
                throw std::runtime_error("Failed to read matrix element.");
            }
        }
    }

    return matrix;
}

void printSubmatrix(const std::vector<std::vector<int>>& matrix, int rowUpperLeft, int columnUpperLeft,
                    int rowLowerRight, int columnLowerRight)
{
    if (matrix.empty() || matrix[0].empty())
    {
        return;
    }

    int rows = static_cast<int>(matrix.size());
    int cols = static_cast<int>(matrix[0].size());

    if (rowUpperLeft < 0 || columnUpperLeft < 0 || rowLowerRight >= rows || columnLowerRight >= cols ||
        rowUpperLeft > rowLowerRight || columnUpperLeft > columnLowerRight)
    {
        throw std::invalid_argument("Invalid submatrix coordinates.");
    }

    for (int i = rowUpperLeft; i <= rowLowerRight; ++i)
    {
        for (int j = columnUpperLeft; j <= columnLowerRight; ++j)
        {
            std::cout << matrix[i][j];
            if (j < columnLowerRight)
            {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
}

}  // namespace kadane