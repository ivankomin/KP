#ifndef VALIDATION_H
#define VALIDATION_H
#include <stdio.h>
#include <ctype.h>
#define MAX_LENGTH 100
char validateFormat(char pick){
    return pick != 'r' && pick != 'm';
}
char validateSortChoice(char pick){
    return pick != 'a' && pick != 'd';
}
unsigned validateIntInput(const char* prompt, const char* errorMessage){
    char validInput = 0;
    unsigned input = 0;
    do {
        printf("%s", prompt);
        validInput = scanf("%u", &input);
        while (getchar() != '\n');
        if (!validInput) {
            printf("Enter a valid number!\n");
        }
        else if(input > MAX_LENGTH || input == 0) {
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

char isAlphabetic(char *str) {
    if (strlen(str) == 0) {
        printf("Input cannot be empty!\n");
        return 0;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i])) {
            printf("Invalid input!\n");
            return 0;
        }
    }
    return 1;
}
#endif