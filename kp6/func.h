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

#endif