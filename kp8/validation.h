#ifndef VALIDATION_H
#define VALIDATION_H
#include <stdio.h>

char validateCircuitChoice(char pick){
    return pick >= '1' && pick <= '4';
}
char isPositive(double val){
    return val > 0.0;
}

char validateChars(const char* prompt, char (*cond)(char), const char* errorMessage){
    char pick = 0;
    do{
        printf("%s", prompt);
        pick = getchar();
        while (getchar() != '\n');
        if (!cond(pick)){
            printf("%s", errorMessage);
        }
    }while (!cond(pick));
    return pick;
}
double validateDoubleInput(const char* prompt, char (*cond)(double),double min, double max, const char* errorMessage){
    char validInput = 0;
    double input = 0.0;
    do {
        printf("%s [%lf, %lf]: ", prompt, min, max);
        validInput = scanf("%lf", &input);
        while (getchar() != '\n');
        if (!validInput) {
            printf("Enter a valid number!\n");
        }
        else if(!cond(input) || input < min || input > max) {
            printf("%s", errorMessage);
            validInput = 0;
        }
    }while (!validInput);
    return input;
}
#endif