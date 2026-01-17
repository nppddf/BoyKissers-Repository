#include <iostream>
#include <limits>

#include "plus.h"

int main()
{
    std::cout << "Summator - enter two integer numbers:\n";

    long long firstNumber  = 0;
    long long secondNumber = 0;
    while (true)
    {
        if (!(std::cin >> firstNumber >> secondNumber))
        {
            std::cout << "Invalid input. Please enter two integers.\n";

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cout << sum(firstNumber, secondNumber) << "\n";
    }
}