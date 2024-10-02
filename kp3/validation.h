#include <stdio.h>
double getValidK(){
    double k = 0;
    int validInput = 0;
        do{
            printf("Enter the root degree (k), k != 0: ");
            validInput = scanf("%lf", &k);
            while (getchar() != '\n');

            if (!validInput) {
                printf("Enter a valid number!\n");
            }
            else if (k == 0) {
                printf("K cannot be equal to 0.\n");
                validInput = 0;
            }
            fflush(stdin);
        } while(!validInput);
    return k;
}

double getValidX(double k){
    double x = 0;
    int validInput = 0;
    do{
            printf("Enter the number (x), Remember: if k is even, then x must be >= 0.\nALSO remember that if you have typed in a non-integer root degree, x CANNOT be negative: ");
            validInput = scanf("%lf", &x);
            while (getchar() != '\n');

            if (!validInput) {
                printf("Enter a valid number!\n");
            }
            else if ((int)k%2 == 0 && x < 0) {
                printf("If k is even, then x must be >= 0!\n");
                validInput = 0;
            }
            fflush(stdin);
        } while(!validInput);
    return x;
}

double getValidE(){
    double e = 0;
    int validInput = 0;
    do{
            printf("Enter the accuracy in exponent (from 1e-15 to 1e-1): ");
            validInput = scanf("%lf", &e);
            while (getchar() != '\n');

            if (!validInput) {
                printf("Enter a valid number!\n");
            }
            else if (e > 0.1 || e < 1e-15) {
                printf("Invalid accuracy!\n");
                validInput = 0;
            }
            fflush(stdin);
        } while(!validInput);
    return e;
}