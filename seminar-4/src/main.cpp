#include <iostream>

#include "../inc/name_utils.h"

int main()
{
    try
    {
        std::cout << "Enter rows and columns, then matrix elements:\n";
        const auto inputMatrix = readMatrix();

        const auto [rowBegin, colBegin, rowEnd, colEnd, bestSum] = maxSumSubmatrix(inputMatrix);

        std::cout << "Max sum: " << bestSum << '\n';
        std::cout << "Submatrix coordinates (r1, c1, r2, c2): " << rowBegin << ' ' << colBegin << ' '
                  << rowEnd << ' ' << colEnd << '\n';
        std::cout << "Submatrix:\n";
        printSubmatrix(inputMatrix, rowBegin, colBegin, rowEnd, colEnd);
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Error: " << exception.what() << '\n';
        return 1;
    }

    return 0;
}