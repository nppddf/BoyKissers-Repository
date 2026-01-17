#include <iostream>
#include <limits>
#include <string>

#include "function_parser.h"

int main()
{
    std::cout << "Function Calculator - enter function (sin(x), cos(x), e^x):\n";

    std::string input;
    while (std::getline(std::cin, input))
    {
        if (input.empty()) {
            continue;
        }

        ParseResult result = parseFunction(input);

        if (!result.success) {
            std::cout << "Invalid input. Please enter sin(x), cos(x), or e^x, where x is a number.\n";
            continue;
        }

        double calculated = calculateFunction(result.type, result.value);
        std::cout << calculated << "\n";
    }
}