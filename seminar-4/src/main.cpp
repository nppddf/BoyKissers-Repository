#include <exception>
#include <iostream>

#include "../inc/kadane_utils.hpp"

int main()
{
    while(true)
    {
        std::cout << "Please, enter the matrix data:\n";

        try
        {
            std::vector<std::vector<int>> matrix = kadane::readMatrix();
            std::tuple<int, int, int, int, int64_t> maxSumSubmatrix =
                kadane::maxSumSubmatrix(matrix);

            std::cout << "Max sum: " << std::get<4>(maxSumSubmatrix) << ", ";
            std::cout << "Coordinates: (" << std::get<0>(maxSumSubmatrix)
                      << ", " << std::get<1>(maxSumSubmatrix) << "), ";
            std::cout << "Coordinates: (" << std::get<2>(maxSumSubmatrix)
                      << ", " << std::get<3>(maxSumSubmatrix) << ")\n";

            std::cout << "Matrix:\n";
            kadane::printSubmatrix(matrix, std::get<0>(maxSumSubmatrix),
                                   std::get<1>(maxSumSubmatrix),
                                   std::get<2>(maxSumSubmatrix),
                                   std::get<3>(maxSumSubmatrix));
        }

        catch(const std::exception&)
        {
            std::cout << "Unexpected error. Exit the program.\n";
            return 1;
        }

        std::cout
            << "All is done. Enter Ctrl^C to exit or try another input.\n";
    }
    return 0;
}