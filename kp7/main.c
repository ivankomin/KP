#include <stdio.h>
#include "validation.h"
int main() {
    printf("This program solves the non linear equation on the interval [a, b].\n");
    do {
        double a = 0, b = 0, e = 0, y = 0;
        char pick = 0;

        printf("What equation would you like to solve?\n");
        printf("1. cos(y/x) - 2sin(1/x) + 1/x = 0\n");
        printf("2. sin(ln(x)) - cos(ln(x)) + y * ln(x) = 0\n");

        pick = validateChars("Enter your choice: ", validateCalcChoice, "Invalid input!\n");

        switch (pick) {
            case '1':
                a = validateDoubleInput("Enter a: ", equalToZero, "a cannot be equal to 0!\n");
                b = validateDoubleInput("Enter b: ", equalToZero, "b cannot be equal to 0!\n");
                y = validateDoubleInput("Enter y: ", anythingGoes, "");
                e = validateDoubleInput("Enter e: ", validateE, "E must be between 1e-15 and 1e-2!\n");
                break;
            case '2':
                a = validateDoubleInput("Enter a: ", greaterThanZero, "a has to be greater than 0!\n");
                b = validateDoubleInput("Enter b: ", greaterThanZero, "b has to be greater than 0!\n");
                y = validateDoubleInput("Enter y: ", anythingGoes, "");
                e = validateDoubleInput("Enter e: ", validateE, "E must be between 1e-15 and 1e-2!\n");
                break;
            default:
                printf("Something went wrong...\n");
                break;
        }
        printf("Press '0' to quit or any other key to continue: ");
    } while (getchar() != 48);
    return 0;
}