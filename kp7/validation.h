#ifndef VALIDATION_H
#define VALIDATION_H
#include <stdio.h>

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
#endif