#include <stdio.h>
#include <time.h>
#include "validation.h"
#include "func.h"
#define MAX_LENGTH 10
#define MIN_LENGTH 2
#define MIN_RANGE -100
#define MAX_RANGE 100

int main(){
    printf("This program solves SLAE using the coefficients and free terms provided by the user.\n");
    srand(time(NULL));
    do{
        unsigned rows = 0;
        double e = 0;
        char pick = 0;
        double *b, *x, *xp;
        double **a;

        rows = validateIntInput("Enter the number of rows (from 2 up to 10): ", MAX_LENGTH, MIN_LENGTH, "The number of rows must be in the required range!\n");

        allocateArrays(rows, &b, &x, &xp, &a);
        if (a == NULL || b == NULL || x == NULL || xp == NULL) {
            printf("Memory allocation error!\n");
            freeArrays(rows, b, x, xp, a);
            return 0;
        }
        e = validateDoubleInput("Enter e (from 1e-15 to 1e-3): ", validateE, "E must be between 1e-15 and 1e-3!\n");
        pick = validateChars("Enter how you want to fill in the coefficients and free terms ('r' for random or 'm' for manual input): ", validateFormat, "Invalid input!\n");
        
        switch(pick){
            case 'm':
                fillSLaeManually(a, b, rows);
                break;
            case 'r': 
                generateSlae(a, b, rows, MIN_RANGE, MAX_RANGE);
                break;
            default:
                printf("Something went wrong...\n");
                freeArrays(rows, b, x, xp, a);
                return 0;
        }
        printInitSlae(rows, a, b);
        solveSlae(a, b, x, xp, rows, e);
        printSolvedCoeffs(rows, x, e);
        printSolvedSlae(rows, a, b, x);

        printf("\nPress '0' to quit or any other key to continue: ");
        freeArrays(rows, b, x, xp, a);
    }while(getchar() != 48);

    return 0;
}
