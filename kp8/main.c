#include <stdio.h>
#include "func.h"
#include "validation.h"
#define ZERO_TO_EXIT 48
#define MAX_VALUE 1e3
#define MIN_VALUE 1e-3

int main(){
    printf("This program calculates complex resistance of a chosen circuit.\n");
    do {
        char choice = 0;
        double r1 = 0.0, r2 = 0.0, c = 0.0, l = 0.0;
        double fmin = 0.0, fmax = 0.0, resFrequency = 0.0, df = 0.0;
        char isR2Needed = 0;
        char *r1Prompt = "Enter R: ";
        printCircuit();
        choice = validateChars("Enter your choice (1-4): ", validateCircuitChoice, "Invalid input!\n");

        switch (choice) {
            case '1':
                printf("You have chosen the first circuit.\n");
                break;
            case '2':
                printf("You have chosen the second circuit.\n");
                break;
            case '3':
                printf("You have chosen the third circuit.\n");
                isR2Needed = 1;
                r1Prompt = "Enter R1: ";
                break;
            case '4':
                printf("You have chosen the fourth circuit.\n");
                isR2Needed = 1;
                r1Prompt = "Enter R1: ";
                break;
            default:
                printf("Where did we go so wrong?\n");
                break;
        }

        l =  validateDoubleInput("Enter L (mHn)", isPositive, MIN_VALUE, MAX_VALUE, "L has to be greater than 0 and in the required range!\n");
        c =  validateDoubleInput("Enter C (mcF)", isPositive, MIN_VALUE, MAX_VALUE, "C has to be greater than 0 and in the required range!\n");
        fmin = validateDoubleInput("Enter fmin (Hz)", isPositive, MIN_VALUE, MAX_VALUE,"fmin has to be greater than 0 and in the required range!\n");
        do {
            fmax = validateDoubleInput("Enter fmax (Hz)", isPositive, MIN_VALUE, MAX_VALUE, "fmax has to be greater than 0 and in the required range!\n");
            if (fmax < fmin) {
                printf("fmax has to be greater than fmin!\n");
            }
        } while (fmax < fmin);
        df = validateDoubleInput("Enter step", isPositive, MIN_VALUE, MAX_VALUE, "Step has to be greater than 0 and in the required range!\n");

        r1 = validateDoubleInput(r1Prompt, isPositive, MIN_VALUE, MAX_VALUE,"R has to be greater than 0 and in the required range!\n");
        if (isR2Needed) {
            r2 = validateDoubleInput("Enter R2", isPositive,MIN_VALUE, MAX_VALUE, "R2 has to be greater than 0 and in the required range!\n");
        }
        
        resFrequency = calculateResonantFrequency(c, l);

        printf("Resonant frequency: %e Hz\n", resFrequency);

        double f = fmin;
        complex numerator = {0.0, 0.0}, denominator = {0.0, 0.0}, result = {0.0, 0.0};

        do{
            const double omega = 2.0 * M_PI * f;
            switch (choice) {
                case '1':
                    calculateCircuit1(&numerator, &denominator, &result, r1, l, c, omega);
                    break;
                case '2':
                    calculateCircuit2(&numerator, &denominator, &result, r1, l, c, omega);
                    break;
                case '3':
                    calculateCircuit3(&numerator, &denominator, &result, r1, r2, l, c, omega);
                    break;
                case '4':
                    calculateCircuit4(&numerator, &denominator, &result, r1, r2, l, c, omega);
                    break;
                default:
                    printf("I told you not to touch that thing!\n");
                    break;
            }
            printf("f = %lf Hz | Z = %e %+ e*i\n", f, result.real, result.imaginary);
            if (f == fmax) {  
                break;
            } 
            else if (f + df > fmax) {
                f = fmax;
            } 
            else {
                f += df; 
            }
        } while (f <= fmax);

        printf("Press '0' to exit or any other key to continue: ");
    } while (getchar() != ZERO_TO_EXIT);

    return 0;
}