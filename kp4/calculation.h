#ifndef CALCULATION_H
#define CALCULATION_H
#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846
double to_rad(double x){
    return x * M_PI / 180.0;
}
double taylorSin(double x, double e) {
    x = fabs(x) <= 360 
            ? to_rad(x)
            : to_rad(fmod(x,2.0*M_PI));
    double n = 1;
    double delta = x, sinx = delta;
    do{
        delta *= -x * x / ((n+1.0)*(n+2.0));
        sinx += delta;
        n+=2;
    }while (fabs(delta) >= e);
    return sinx;
}
double taylorCos(double x, double e) {
    x = fabs(x) <= 360 
            ? to_rad(x)
            : to_rad(fmod(x,2.0*M_PI));
    double n = 1;
    double delta = 1, cosx = delta;
    do{
        delta *= -x * x / (2.0*n*(2.0*n-1.0));
        cosx += delta;
        n++;
    }while (fabs(delta) >= e);
    return cosx;
}
#endif