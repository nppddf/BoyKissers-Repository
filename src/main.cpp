#include "input_or_output_check.h"
#include <iostream>

int main(void) {
    char line[1024], operation = 0;
    double num1 = 0, num2 = 0;
    std::cout << "Use * - + / to make calculations, write the expression in the form: num1 "
                 "(arithmetic operator) num2\n";
    while (1) {
        if (!fgets(line, sizeof(line), stdin)) {
            break;
        }
        if ((sscanf(line, "%lf %c %lf", &num1, &operation, &num2) == 3) &&
            (input(num1) == 1 && input(num2) == 1)) {
            output(num1, operation, num2);
        } else {
            std::cout << ("Incorrect input, try again\n");
        }
    }
    return 0;
}