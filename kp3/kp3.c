#include <stdio.h>
#include <math.h>
#include "calculations.h"
#include "validation.h"

int main() {
    printf("This program calculates the K-th root of an X with specified precision (E).\n");
    double k = 0, x = 0, e = 0, y = 0;

    do{
        k = getValidK();
        x = getValidX(k);
        e = getValidE();

        y = kthRoot(k, x, e);

        printf("Result (as a float): %.*lf\n",(int)fabs(log10(e)), y);
        printf("Result (as an exponent): %e\n", y);
        
        printf("Press '0' to quit or any other key to continue: ");

    } while (getchar() != 48);

    return 0;
}