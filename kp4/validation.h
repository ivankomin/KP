#ifndef VALIDATION_H
#define VALIDATION_H
#include <stdio.h>

char validateE(double e){
    return e >= 1e-15 && e <= 1e-1;
}
char dxNegative(double dx){
    return dx < 0 && dx != 0;
}
char dxPositive(double dx){
    return dx > 0 && dx != 0;
}
char validateCalcChoice(char pick){
    return pick != '1' && pick != '2';
}

char validateFormat(char pick){
    return pick != 'f' && pick != 'e';
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
double validateGeneralInput(const char* prompt, char (*cond)(double), const char* errorMessage){
    char validInput = 0;
    double input = 0;
    do {
        printf("%s", prompt);
        validInput = scanf("%lf", &input);
        while (getchar() != '\n');
        if (!validInput) {
            printf("Enter a valid number!\n");
        }
        else if(cond != NULL && !cond(input)){
            printf("%s", errorMessage);
            validInput = 0;
        }
    }while (!validInput);
    return input;
}

double validateDx(char cond){
    switch (cond){
        case 1:
            return validateGeneralInput("Enter dx (>0): ", dxPositive, "Dx has to be positive!\n");
        case 2:
            return validateGeneralInput("Enter dx (<0): ", dxNegative, "Dx has to be less than 0!\n");
        default:
            printf("I dont know how you managed to do this, but you broke the program. Nice\n");
    }
}
#endif


