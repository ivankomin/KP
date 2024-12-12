#include <stdio.h>
#include <math.h>

double findX1(double x, double y){
    return (cos(y/x)-2.0*sin(1.0/x)+1.0/x);
}

double findX2(double x, double y){
    return (sin(log(x)) - cos(log(x)) + y * log(x));
}

double solveBisection(double (*func)(double, double), double y, double a, double b, double e, int maxIters){
    if ((*func)(a, y) * (*func)(b, y) > 0) {
        return 0;
    }
    double x = 0;
    int iters = 0;
    do{
        x = (a + b) / 2.0;
        ((*func)(x, y) * (*func)(a, y) > 0) ? (a = x) : (b = x);
        iters++;
    }while (fabs(b - a) >= e && iters <= maxIters);
    if (iters == maxIters) {
        printf("Bisection method didn't converge within the maximum number of iterations.\n");
        return 0;
    }
    else {
        printf("Solved in %d iterations\n", iters);
        return x;
    }
}

double solveNewton(double (*function)(double, double), double y, double a, double b, double e, double reallySmallNumber, double minDerivative, int maxIters) {
    double delta = 0;
    double derivative = 0;
    int iters = 0;

    double x = (a + b) / 2.0;

    do {
        double fx = function(x, y);
        if (isnan(fx))
        {
            printf("Function is undefined at x = %lf. Skipping...\n", x);
            return 0;
        }
        derivative = (function(x + reallySmallNumber, y) - fx) / reallySmallNumber;

        if (fabs(derivative) < minDerivative) {
            printf("Derivative too small at x = %lf. The method may not converge.\n", x);
            return 0;
        }
        delta = fx / derivative;
        x -= delta;

        iters++;
        if (iters > maxIters) {
            printf("Maximum iterations reached. The method may not converge.\n");
            return 0;
        }
    } while (fabs(delta) > e);

    return x;
}

