#include <stdio.h>
#include <math.h>
#include "validation.h"
#include "calculation.h"

void printArray(double x1, double x2, double dx, double e, double (*taylorFunc)(double, double), double libFunc(double), char outputFormat);

int main() {
    printf("This program calculates the sine and cosine of the range of angles from x1 to x2 with step dx with specified precision (e).\n");

    do {
        double x1 = 0, x2 = 0, e = 0, dx = 0;
        char pick = 0, outputFormat = 0;
        x1 = validateGeneralInput("Enter x1: ", NULL, "");
        x2 = validateGeneralInput("Enter x2: ", NULL, "");
        dx = x1 == x2 
                ? 0 
                : x1 < x2 
                        ? validateDx(1) 
                        : validateDx(2);
        e = validateGeneralInput("Enter e (from 1e-15 to 1e-1): ", validateE, "E must be between 1e-15 and 1e-1!\n");
        
        pick = validateChars("Enter what you want to calculate ('1' for sin or '2' for cos): ", validateCalcChoice, "Invalid input!\n");
        outputFormat = validateChars("Enter output format ('f' for float or 'e' for exponent): ", validateFormat, "Invalid input!\n");

        pick == '1' ? printArray(x1, x2, dx, e, taylorSin, sin, outputFormat) : printArray(x1, x2, dx, e, taylorCos, cos, outputFormat);  
        
        printf("Press '0' to quit or any other key to continue: ");
    }while (getchar () != 48);

    return 0;
}

void printArray(double x1, double x2, double dx, double e, double (*taylorFunc)(double, double), double libFunc(double), char outputFormat) {
    double x = 0;
    int size = dx == 0 
            ? 1 
            : ((x2 - x1) / dx) + 1;
    double taylorArray[size], libArray[size];
    if (x1 == x2) {
        taylorArray[0] = taylorFunc(x1, e);
        libArray[0] = libFunc(to_rad(x1));
    }
    else{
        int i = 0;
        x = x1;
        do {
            taylorArray[i] = taylorFunc(x, e);
            libArray[i] = libFunc(to_rad(x));
            i++;
            x += dx;
        } while (x1 < x2 
                ? x <= x2 
                : x >= x2);
    }
    printf("%-20s%-25s%-25s%-25s\n", "x", "Lib Value", "Taylor Value", "Difference");

    for (int j = 0; j < size; j++) {
        if (outputFormat == 'f') {
            printf("%-20.*lf|%-25.*lf|%-25.*lf|%-25e\n", (int)fabs(log10(e)), x1 + j * dx,
            (int)fabs(log10(e)), libArray[j], 
            (int)fabs(log10(e)), taylorArray[j], 
            fabs(libArray[j] - taylorArray[j]));
        }
        else{
            printf("%-20e|%-25e|%-25e|%-25e\n", x1 + j * dx, libArray[j], taylorArray[j], fabs(libArray[j] - taylorArray[j]));
        }       
    }
}