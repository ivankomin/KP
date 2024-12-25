#ifndef VALIDATION_H
#define VALIDATION_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_NAME_LENGTH 40
#define FORBIDDEN_CHARS "/\\:*?\"<>|()!@#$&^?;¬~'"
FILE *file;
// TODO this is an absolute mess of a file that im totally gonna clean up (i won't)

//------------------CONDITIONS------------------
char tooLong(const char* str) {
    return strlen(str) > MAX_NAME_LENGTH;
}
char containsForbiddenChars(const char* str) {
    return strpbrk(str, FORBIDDEN_CHARS) != NULL;
}
char isPositive(double num) {
    return num > 0.0;
}
char optionInRange(unsigned option) {
    return option >= 0 && option <= 10;
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

//------------------INPUT------------------

char validateOption(const char* prompt, char (*cond)(unsigned), const char* errorMessage) {
    char validInput = 0;
    unsigned input = 0;
    do {
        printf("%s", prompt);
        validInput = scanf("%u", &input);
        while (getchar() != '\n');
        if (!validInput) {
            printf("Enter a valid number!\n");
        }
        else if(!cond(input)) {
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

char* validateStringInput(const char* prompt, char (*cond)(char*), const char* errorMessage) {
    char validInput = 0;
    char static input[MAX_NAME_LENGTH];
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

//------------------FILES------------------

char* validateFileName() {
    char validInput = 0;
    static char fileName[MAX_NAME_LENGTH]; 
    do {
        printf("Enter file name: ");
        validInput = scanf("%s", fileName); 
        while (getchar() != '\n'); 
        if (containsForbiddenChars(fileName)) {
            printf("File name contains forbidden characters!\n");
            validInput = 0;
        }
        else if (tooLong(fileName)) {
            printf("File name is too long!\n");
            validInput = 0;
        }
    } while (!validInput);
    
    return fileName; 
}

char fileAlreadyExists(const char* fileName) {
    file = fopen(fileName, "r");
    if (file == NULL) {
        return 0;
    }
    fclose(file);
    return 1;
}

char* getNewFileName() {
    char* fileName;
    do{
        fileName = validateFileName();
        if (fileAlreadyExists(fileName)) {
            printf("File already exists!\n");
        }
    } while (fileAlreadyExists(fileName));
    return fileName;
}
char* getExistingFileName() {
    char* fileName;
    do{
        fileName = validateFileName();
        if (!fileAlreadyExists(fileName)) {
            printf("File does not exist!\n");
        }
    } while (!fileAlreadyExists(fileName));
    return fileName;
}
#endif