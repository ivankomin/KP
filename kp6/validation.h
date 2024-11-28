#ifndef VALIDATION_H
#define VALIDATION_H
#include <stdio.h>
char validateFormat(char pick){
    return pick != 'r' && pick != 'm';
}
char validateE(double e){
    return e >= 1e-15 && e <= 1e-3;
}
char validateDouble(double d){
    return d != 0 && d <= 1e6 && d >= -1e6;
}
unsigned validateIntInput(const char* prompt,const unsigned MAX_LENGTH, const unsigned MIN_LENGTH, const char* errorMessage){
    char validInput = 0;
    unsigned input = 0;
    do {
        printf("%s", prompt);
        validInput = scanf("%u", &input);
        while (getchar() != '\n');
        if (!validInput) {
            printf("Enter a valid number!\n");
        }
        else if(input > MAX_LENGTH || input < MIN_LENGTH) {
            printf("%s", errorMessage);
            validInput = 0;
        }
    }while (!validInput);
    return input;
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