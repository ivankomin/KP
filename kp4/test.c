#include <stdio.h>
#include <math.h>
#include "validations.h"

#define PI 3.14159265358979323846
double to_rad(double x) { return x * PI / 180; }
int main() {
    printf("This program calculates the sinus and cosinus of an the range of angles from x1 to x2 with specified precision (e).\n");
    double x1 = 0, x2 = 0, e = 0, dx = 0, delta = 0, x = 0;
    double sinTaylor = 0, cosTaylor = 0;
    int n = 1;

    do {
        printf("Enter x: ");
        scanf("%lf", &x);
        x = to_rad(x);
        double sinx = sin(x);
        printf("sin(%lf) = %lf\n", x, sinx);
        
        printf("Enter e (from 1e-15 to 1e-1): ");
        scanf("%lf", &e);

        delta = x;
        sinTaylor = delta;
        do{
            delta *= -x *x / ((n+1)*(n+2));
            sinTaylor += delta;
            n+=2;
        }while (fabs(delta) >= e);
        printf ("sinTaylor(%lf) = %lf\n", x, sinTaylor);
        printf("The difference is: %lf\n", sinTaylor - sinx);

        printf("Press '0' to quit or any other key to continue: ");
    }while (getchar () != 48);

    return 0;
}