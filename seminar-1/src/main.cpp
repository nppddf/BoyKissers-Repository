#include "plus.h"

#include <iostream>

int main(void) {
    std::cout << "Use * - + / to make calculations, write the expression in the form: num1 "
                 "(arithmetic operator) num2\n";

    LL first_number = 0;
    LL second_number = 0;
    while (true) {
        try {
        std::cin >> first_number >> second_number;
        }
        catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }

        std::cout << sum(first_number, second_number);
    }

    return 0;
}