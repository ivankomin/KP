#ifndef VALIDATION_H
#define VALIDATION_H
#include <stdio.h>
#include <math.h>

char validateK(double k){
    return k != 0;
}
char validateX(double x, double k){
    if ((int)k%2 == 0 && x < 0){
        return 0;
    }
    else if (floor(k) != k && x < 0){
        return 0;
    }
    return 1;
}
char validateE(double e){
    return e >= 1e-15 && e <= 1e-1;
}

double validateGeneralInput(const char* prompt, char (*cond)(double, double),double k, const char* errorMessage){
    char validInput = 0;
    double input = 0;
    do{
        printf("%s", prompt);
        validInput = scanf("%lf", &input);
        while (getchar() != '\n');
        if (!validInput){
            printf("Enter a valid number!\n");
        }
        else if (!cond(input, k)){
            printf("%s", errorMessage);
            validInput = 0;
        }
    }while (!validInput);

    return input;
}

#endif
