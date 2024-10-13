#include <stdio.h>
#include <math.h>
#include "calculations.h"
#include "validation.h"

int main() {
    printf("This program calculates the K-th root of an X with specified precision (E).\n");
    double k = 0, x = 0, e = 0, y = 0;

    do{
        k = validateGeneralInput("Enter the root degree (k): ", (char (*)(double, double))validateK, 0, "K cannot be equal to 0!\n");
        x = validateGeneralInput("Enter the radical (x)\nConditions to remember: if k is even, x cannot be negative; if k is not an integer, x cannot be negative: ", validateX, k, "Invalid input. Read the conditions carefully please :)\n");
        e = validateGeneralInput("Enter the accuracy (e) (from 1e-15 to 1e-1): ", (char (*)(double, double))validateE, 0, "The accuracy is not within the required range!\n");

        y = kthRoot(k, x, e);

        printf("Result (as a float): %.*lf\n",(int)fabs(log10(e)), y);
        printf("Result (as an exponent): %e\n", y);
        
        printf("Press '0' to quit or any other key to continue: ");

    } while (getchar() != 48);

    return 0;
}