#include <stdio.h>
#include <math.h>
#include "calculations.h"
#include "validation.h"

int main() {
    printf("This program calculates the K-th root of an X with specified precision (E).\n");
    double k = 0, x = 0, e = 0;

    do{
        k = getValidK();
        x = getValidX(k);
        e = getValidE();

        double y = kthRoot(k, x, e);

        printf("Result: %.*lf\n",(int)fabs(log10(e)), y);
        
        printf("Press 'q' to quit or any other key to continue: ");
        fflush(stdin);

    } while (getchar() != 'q');

    return 0;
}