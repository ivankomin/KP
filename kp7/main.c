#include <stdio.h>
#include "validation.h"
#include "func.h"
#define MAX_ITERS 10000
int main() {
    printf("This program solves non linear equations on the interval [a, b].\n");
    do {
        double a = 0, b = 0, e = 0, y = 0, x = 0;
        char pick = 0;
        double (*chosenFunc)(double, double);
        char (*chosenCondition)(double);
        char *errorMessage = "";

        printf("Which equation would you like to solve?\n");
        printf("1. cos(y/x) - 2sin(1/x) + 1/x = 0\n");
        printf("2. sin(ln(x)) - cos(ln(x)) + y * ln(x) = 0\n");

        pick = validateChars("Enter your choice: ", validateCalcChoice, "Invalid input!\n");

        switch (pick) {
            case '1':
                printf("The chosen equation is: cos(y/x) - 2sin(1/x) + 1/x = 0\n");
                chosenCondition = equalToZero;
                chosenFunc = findX1;
                errorMessage = "a or b cannot be equal to 0!\n";
                break;
            case '2':
                printf("The chosen equation is: sin(ln(x)) - cos(ln(x)) + y * ln(x) = 0\n");
                chosenCondition = greaterThanZero;
                chosenFunc = findX2;
                errorMessage = "a or b must be greater than 0!\n";
                break;
            default:
                printf("Something went wrong...\n");
                break;
        }
        
        a = validateDoubleInput("Enter a: ", chosenCondition, errorMessage);
        do{
            b = validateDoubleInput("Enter b (>a): ", chosenCondition, errorMessage);
        } while (b <= a);
        y = validateDoubleInput("Enter y: ", anythingGoes, "");
        e = validateDoubleInput("Enter e: ", validateE, "E must be between 1e-15 and 1e-2!\n");

        pick = validateChars("Enter how you want to solve the equation ('1' for bisection or '2' for Newton): ", validateCalcChoice, "Invalid input!\n");

        switch(pick) {
            case '1':
                x = solveBisection(chosenFunc, y, a, b, e, MAX_ITERS);
                break;
            case '2':
                x = solveNewton(chosenFunc, y, a, b, e, MAX_ITERS);
                break;
            default:
                printf("Something went wrong...\n");
                break;
        }
        if (x == 0) {
            printf("No solutions were found on the interval [%lf, %lf]\n", a, b);
        }
        else{
        printf("Result: x = %.*lf\n", (int)fabs(log10(e)), x);
        }
        printf("Press '0' to quit or any other key to continue: ");
    } while (getchar() != 48);
    return 0;
}