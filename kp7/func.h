#include <stdio.h>
#include <math.h>

double findX1(double x){
    return (cos(2.0/x)-2.0*sin(1.0/x)+1.0/x);
}

double findX2(double x){
    return (sin(log(x)) - cos(log(x)) + 2.0 * log(x));
}

double solveHalfMethod(double (*func)(double), double a, double b, double e){
    double x = 0;
    do{
        x = (a + b) / 2.0;
        ((*func)(x) * (*func)(a) > 0) ? (b = x) : (a = x);
    }while (fabs(b - a) >= e);
    return x;
}