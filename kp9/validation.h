#ifndef VALIDATION_H
#define VALIDATION_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_NAME_LENGTH 40
#define FORBIDDEN_CHARS "/\\:*?\"<>|()!@#$&^?;¬~'"
FILE *file;

//conditions
char tooLong(const char* str) {
    return strlen(str) > MAX_NAME_LENGTH;
}
char containsForbiddenChars(const char* str) {
    return strpbrk(str, FORBIDDEN_CHARS) != NULL;
}
char isPositive(double num) {
    return num > 0.0;
}
char optionInRange(char option) {
    return option >= '0' && option <= '9';
}
char sortByInRange(char option) {
    return option >= '1' && option <= '3';
}
char sortOrderInRange(char option) {
    return option == '1' || option == '2';
}
char yesNo(char option) {
    return option == 'y' || option == 'Y' || option == 'n' || option == 'N';
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

//input
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

unsigned validateIntInput(const char* prompt, unsigned min, unsigned max, const char* errorMessage){
    unsigned input;
    int validInput = 0;
    do {
        printf("%s", prompt);
        validInput = scanf("%u", &input);
        while (getchar() != '\n');
        if (!validInput) {
            printf("Enter a valid number!\n");
        } else if (input < min || input > max) {
            printf("%s", errorMessage);
            validInput = 0;
        }
    } while (!validInput);
    return input;
}

double validateDoubleInput(const char* prompt, char (*cond)(double), const char* errorMessage){
    char validInput = 0;
    double input = 0.0;
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

char* validateStringInput(const char* prompt, char (*cond)(char*), const char* errorMessage) {
    char validInput = 0;
    static char input[2];
    do {
        printf("%s", prompt);
        validInput = scanf("%s", input);
        while (getchar() != '\n');
        if (!validInput) {
            printf("Enter a valid string!\n");
        }
        else if (!cond(input)) {
            printf("%s", errorMessage);
            validInput = 0;
        }
    } while (!validInput);
    return input;

}

//files
char fileAlreadyExists(const char* fileName) {
    file = fopen(fileName, "r");
    if (file == NULL) {
        return 0;
    }
    fclose(file);
    return 1;
}

char getNewFileName(char* fileName) {
    return (!fileAlreadyExists(fileName));
}

char getExistingFileName(char* fileName) {
    return (fileAlreadyExists(fileName));
}
void appendSignature(char* fileName) {
    if (strlen(fileName) < 4 || strcmp(&fileName[strlen(fileName) - 4], ".csv") != 0) {
        strcat(fileName, ".csv");
    }
}

char* validateFileName(char (*cond)(char*), const char* errorMessage) {
    char validInput = 0;
    static char fileName[MAX_NAME_LENGTH]; 
    do {
        printf("Enter file name (only alphanumeric characters, max %d characters): ", MAX_NAME_LENGTH);
        validInput = scanf("%s", fileName); 
        while (getchar() != '\n'); 
        if (containsForbiddenChars(fileName) || tooLong(fileName)) {
            printf("Invalid file name!\n");
            validInput = 0;
        }
        else {
            appendSignature(fileName);
            if (!cond(fileName)) {
                printf("%s", errorMessage);
                validInput = 0;
            }
        }
    } while (!validInput);
    return fileName; 
}
#endif