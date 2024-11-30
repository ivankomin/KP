#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include <stdlib.h>

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

void printInitSlae(unsigned rows, double **a, double *b) {
    printf("Initial SLAE: \n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            if(j == 0) {
                printf(" %.1lf*x%d", a[i][j], j+1);
            } else {
                printf(" %+.1lf*x%d", a[i][j], j+1);
            }
        }
    }
}
#endif