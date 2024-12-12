#ifndef VALIDATION_H
#define VALIDATION_H
#include <stdio.h>
#define UNIQUE_TOLERANCE 1e-6
#define ASYMPTOTE_THRESHOLD 1e6
char equalToZero(double val){
    return val != 0;
}
char greaterThanZero(double val){
    return val > 0;
}
char anythingGoes(double val){
    return 1;
}
char validateE(double val){
    return val >= 1e-15 && val <= 1e-2;
}
char validateCalcChoice(char pick){
    return pick != '1' && pick != '2';
}
double validateDoubleInput(const char* prompt, char (*cond)(double), const char* errorMessage){
    char validInput = 0;
    double input = 0;
    do {
        printf("%s", prompt);
        validInput = scanf("%lf", &input);
        while (getchar() != '\n');
        if (!validInput) {
            printf("Enter a valid number!\n");
        }
        else if(!cond(input)){
            printf("%s", errorMessage);
            validInput = 0;
        }
    }while (!validInput);
    return input;
}
char validateChars(const char* prompt, char (*cond)(char), const char* errorMessage){
    char pick = 0;
    do{
        printf("%s", prompt);
        pick = getchar();
        while (getchar() != '\n');
        if (cond(pick)){
            printf("%s", errorMessage);
        }
    }while (cond(pick));
    return pick;
}

char isAsymptote(double funcStart, double funcEnd) {
    return fabs(funcStart) > ASYMPTOTE_THRESHOLD || fabs(funcEnd) > ASYMPTOTE_THRESHOLD || fabs(funcStart - funcEnd) > ASYMPTOTE_THRESHOLD;
}

char isUniqueRoot(double roots[], int rootsFound, double newRoot) {
    for (int i = 0; i < rootsFound; i++) {
        if (fabs(roots[i] - newRoot) < UNIQUE_TOLERANCE) {
            return 0;
        }
    }
    return 1;
}
#endif