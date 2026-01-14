#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "math_func.h"

int input(double n)
{
    char str[100];
    snprintf(str, sizeof(str), "%lf", n);
    for (int i = 0; i < strlen(str);i++)
    {
        if (!isdigit(str[i]) && str[i] != '.' && str[i] != '-')
        {
            printf("Error: Not a number\n");
            return 0;
        }
    }
    return 1;
}

void output(double num1, char operation, double num2) 
{
    if (operation == '+')
    {
        printf("%lf\n", summ(num1, num2));
    } 
    else if (operation == '-')
    {
        printf("%lf\n", difference(num1, num2));
    } 
    else if (operation == '*')
    {
        printf("%lf\n", composition(num1, num2));
    } 
    else if (operation == '/')
    {
        if (num2 == 0) 
        {
            printf("Error: Division by zero\n");
        } 
        else 
        {
            printf("%lf\n", division(num1, num2));
        }
    } 
    else 
    {       
        printf("Error: Unknown operation\n");
    }
}