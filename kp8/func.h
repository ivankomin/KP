#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846
typedef struct {
    double real;
    double imaginary;
} complex;

complex divideComplex(complex c1, complex c2){
    complex result = {0.0, 0.0};
    double denominator = c2.real * c2.real + c2.imaginary * c2.imaginary;
    if (denominator == 0.0){
        printf("Division by zero!\n");
        result.real = 0.0;
        result.imaginary = 0.0;
        return result;
    }
    result.real = (c1.real * c2.real + c1.imaginary * c2.imaginary) / denominator;
    result.imaginary = (c1.imaginary * c2.real - c1.real * c2.imaginary) / denominator;
    return result;
}
void printCircuit(){
    printf("Which circuit do you want to calculate?\n");
    printf("1. \n");
    printf(        "●─┬────────▆▆▆──────◠◠◠◠────┬─●\n"
                   "  │         R         L     │\n"
                   "  │                         │\n"
                   "  │               C         │\n"
                   "  └───────────────││────────┘\n");
    printf("2. \n");
    printf(        "●─┬────────▆▆▆──────││──────┬─●\n"
                   "  │         R       C       │\n"
                   "  │                         │\n"
                   "  │      L                  │\n"
                   "  └────◠◠◠◠─────────────────┘\n");
    printf("3. \n");
    printf(        "●─┬─────────▆▆▆──────││─────┓\n"
                   "  │         R2         C    │\n"
                   "  │                         │\n"
                   "  █ R1     L                │\n"
                   "●─┴──────◠◠◠◠───────────────┘\n");
    printf("4. \n");
    printf(        "●─┬────────▆▆▆──────────────┓\n"
                   "  █ R1     R2               │\n"
                   "  ┴                         │\n"
                   "  ┬ C       L               │\n"
                   "●─┴───────◠◠◠◠──────────────┚\n");

}

double calculateResonantFrequency(double c, double l) {
    return 1.0 / (2.0 * M_PI * sqrt(l * c));
}

void calculateCircuit1(complex *numerator, complex *denominator, complex *result, double r, double l, double c, double omega) {
    numerator->real = l/c;
    numerator->imaginary = -r/(omega*c);
    denominator->real = r;
    denominator->imaginary = omega*l - 1.0/(omega*c);
    *result = divideComplex(*numerator, *denominator);
}

void calculateCircuit2(complex *numerator, complex *denominator, complex *result, double r, double l, double c, double omega) {
    numerator->real = l/c;
    numerator->imaginary = r/(omega*c);
    denominator->real = r;
    denominator->imaginary = omega*l - 1.0/(omega*c);
    *result = divideComplex(*numerator, *denominator);
}

void calculateCircuit3(complex *numerator, complex *denominator, complex *result, double r1, double r2, double l, double c, double omega) {
    numerator->real = r1*r2;
    numerator->imaginary = r1*(omega*l - 1.0/(omega*c));
    denominator->real = r1 + r2;
    denominator->imaginary = omega*l - 1.0/(omega*c);
    *result = divideComplex(*numerator, *denominator);
}

void calculateCircuit4(complex *numerator, complex *denominator, complex *result, double r1, double r2, double l, double c, double omega) {
    numerator->real = r1 * r2 + l/c;
    numerator->imaginary = omega*l*r1 - r2/(omega*c);
    denominator->real = r1+r2;
    denominator->imaginary = omega*l - 1.0/(omega*c);
    *result = divideComplex(*numerator, *denominator);
}
#endif