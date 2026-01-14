#include <>

int main() {
    char line[1024],operation;
    double num1 = 0,num2 = 0;
    printf("Use * - + / to make calculations, write the expression in the form: num1 (arithmetic operator) num2\n");
    while(1)
    {
        if (!fgets(line, sizeof(line), stdin)) 
        {
            break;
        }
        if ((sscanf(line, "%lf %c %lf", &num1, &operation, &num2) == 3) && (input(num1) == 1 && input(num2) == 1))  {
            output(num1, operation, num2);
        }
        else
        {
            printf("Incorrect input, try again\n");
        }
    }
    return 0;
}