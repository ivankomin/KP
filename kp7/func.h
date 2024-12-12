#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include <math.h>
#include "validation.h"
double findX1(double x, double y){
    return (cos(y/x)-2.0*sin(1.0/x)+1.0/x);
}

double findX2(double x, double y){
    return (sin(log(x)) - cos(log(x)) + y * log(x));
}

double solveBisection(double (*func)(double, double), double y, double a, double b, double e, int maxIters){
    double x = 0;
    int iters = 0;
    do{
        x = (a + b) / 2.0;
        ((*func)(x, y) * (*func)(a, y) > 0) ? (a = x) : (b = x);
        iters++;
        if (iters == maxIters) {
            printf("Bisection method didn't converge within the maximum number of iterations.\n");
            return 0;
        }
    } while (fabs(b - a) >= e && iters <= maxIters);
    return x;
}

double solveNewton(double (*function)(double, double), double y, double a, double b, double e, double reallySmallNumber, double minDerivative, int maxIters) {
    double delta = 0;
    double derivative = 0;
    int iters = 0;
    double x = (a + b) / 2.0;
    do {
        if (isnan(function(x, y))){
            return 0;
        }
        derivative = (function(x + reallySmallNumber, y) - function(x, y)) / reallySmallNumber;
        if (fabs(derivative) < minDerivative) {
            return 0;
        }
        delta = function(x, y) / derivative;
        x -= delta;
        iters++;
        if (iters == maxIters) {
            printf("Newton method didn't converge within the maximum number of iterations.\n");
            return 0;
        }
    } while (fabs(delta) >= e && iters <= maxIters);
    return x;
}

#endif