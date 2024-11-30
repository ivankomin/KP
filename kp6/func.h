#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "validation.h"

void allocateArrays(unsigned rows, double **b, double **x, double **xp, double ***a) {
    *b = (double *)calloc(rows, sizeof(double));
    *x = (double *)calloc(rows, sizeof(double));
    *xp = (double *)calloc(rows, sizeof(double));

    *a = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
        (*a)[i] = (double *)calloc(rows, sizeof(double));
    }
}

void freeArrays(int rows, double *b, double *x, double *xp, double **a) {
    free(b);
    free(x);
    free(xp);
    
    for (int i = 0; i < rows; i++) {
        free(a[i]);
    }
    free(a); 
}

double generateRandomDouble(double min, double max) {
    return min + (max - min) * (double)rand() / (RAND_MAX + 1.0);
}
void fillSLaeManually(double **a, double *b, int rows) {
    double diagonalElement = 0, sum = 0;
    for (int i = 0; i < rows; i++) {
        diagonalElement = 0;
        sum = 0;
        do{
            for (int j = 0; j < rows; j++) {
                printf("Enter a%d%d in the range [-100, 100]\n", i + 1, j + 1);
                if (i == j){
                    do{
                        a[i][j] = validateDoubleInput("Input goes here (NOT 0): ", validateDouble, "Invalid input!\n");
                        diagonalElement = fabs(a[i][j]);
                    } while(a[i][j] == 0);
                }
                else{
                    a[i][j] = validateDoubleInput("Input goes here: ", validateDouble, "Invalid input!\n");
                    sum += fabs(a[i][j]);
                }
            }
            if (sum >= diagonalElement) {
                printf("The sum of the coefficients of the row must be less than the coefficient of the diagonal element!\nRe-enter row %d\n", i + 1);
            }
        } while(sum >= diagonalElement);
        printf("Enter b of the row %d in the range [-100, 100]\n", i + 1);
        b[i] = validateDoubleInput("Input goes here: ", validateDouble, "Invalid input!\n");
    }
}
void generateSlae(double **a, double *b, int rows, double min, double max) {
    for (int i = 0; i < rows; i++) {
        double sum = 0;
        for (int j = 0; j < rows; j++) {
            if (i != j) {
                a[i][j] = generateRandomDouble(min, max);
                sum += fabs(a[i][j]); 
            }
        }
        a[i][i] = sum + generateRandomDouble(1.0, 10.0);
        
        b[i] = generateRandomDouble(min, max);
    }
}

void solveSlae(double **a, double *b, double *x, double *xp, int rows, double e) {
    double sum = 0, maxDelta = 0;
    do{
        maxDelta = 0;
        for (int i = 0; i < rows; i++) {
            sum = 0;
            for (int j = 0; j < rows; j++) {
                if (i != j) {
                    sum += a[i][j] * xp[j];
                }
            }
            x[i] = (b[i] - sum) / a[i][i];
            maxDelta = fmax(maxDelta, fabs(x[i] - xp[i]));
        }
        for (int i = 0; i < rows; i++) {
            xp[i] = x[i];
        }
    } while(maxDelta > e);
}

void printInitSlae(unsigned rows, double **a, double *b) {
    printf("\nInitial SLAE: \n\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            if(j == 0) {
                printf(" %.2lf*x%d", a[i][j], j+1);
            } else {
                printf(" %+.2lf*x%d", a[i][j], j+1);
            }
        }
        printf(" = %.2lf\n", b[i]);
    }
}

void printSolvedCoeffs(unsigned rows, double *x, double e) {
    printf("\nThe solved coefficients: \n\n");
    for (int i = 0; i < rows; i++) {
        printf("x%d = %.*lf\n", i+1, (int)fabs(log10(e)), x[i]);
    }
}
void printSolvedSlae(unsigned rows, double **a, double *b, double *x) {
    printf("\nSolved SLAE: \n\n");
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < rows; j++){
            if(j == 0) {
                printf(" %.2lf*%.2lf", a[i][j], x[j]);
            } else {
                printf(" %+.2lf*%.2lf", a[i][j], x[j]);
            }
        }
        printf(" = %.2lf\n", b[i]);
    }
}
#endif