#include "plus.h"

#include <iostream>
#include <limits>

int main(void) {
    std::cout << "Summator - enter two integer numbers:\n";

    long long first_number = 0;
    long long second_number = 0;
    while (true) {
        if (!(std::cin >> first_number >> second_number)) {
            std::cout << "Invalid input. Please enter two integers.\n";

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cout << sum(first_number, second_number) << "\n";
    }
}