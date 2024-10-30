#ifndef CALCULATIONS_H
#define CALCULATIONS_H
#include <stdio.h>
#include <math.h>
double kthRoot(double k, double x, double e) {
    double y = 1;
    double d = 1;

    do{
        if (k < 0){
        k = -k;
        x = 1.0/x;
        }
        d = (1.0 / k) * (x / pow(y, k - 1.0) - y);
        y+=d;
    } while (fabs(d) >= e);
    return y;
}

#endif