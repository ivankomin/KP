#include <stdio.h>
#include <math.h>
double kthRoot(double k, double x, double e) {
    double y = 1;
    double d = 0;
    int i = 1;

    if (k < 0){
        k = -k;
        x = 1.0/x;
    }
    do{
        d = 1/k*(x/pow(y,k-1)-y);
        y+=d;
        printf("Iteration %d, delta: %lf, y = %lf\n", i, d, y);
        i++;
    } while (fabs(d) >= e);
    return y;
}