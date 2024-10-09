#include <stdio.h>
#include <math.h>
double kthRoot(double k, double x, double e) {
    double y = 1;
    double d = 0;

    if (k < 0){
        k = -k;
        x = 1.0/x;
    }
    do{
        d = (1.0 / k) * (x / pow(y, k - 1) - y);
        y+=d;
    } while (fabs(d) >= e);
    return y;
}