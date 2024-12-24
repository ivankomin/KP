#ifndef VALIDATION_H
#define VALIDATION_H
#include <stdio.h>
#include <string.h>
#define MAX_NAME_LENGTH 40
#define FORBIDDEN_CHARS "/\\:*?\"<>|()!@#$&^?;¬~'"
FILE *file;
// TODO this is an absolute mess of a file that im totally gonna clean up (i won't)
char fileAlreadyExists(const char* fileName) {
    file = fopen(fileName, "r");
    if (file == NULL) {
        return 0;
    }
    fclose(file);
    return 1;
}
char tooLong(const char* str) {
    return strlen(str) > MAX_NAME_LENGTH;
}
char containsForbiddenChars(const char* str) {
    return strpbrk(str, FORBIDDEN_CHARS) != NULL;
}
char* validateFileName() {
    char validInput = 0;
    char static fileName[MAX_NAME_LENGTH]; 
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
char* getNewFileName() {
    char* fileName;
    do{
        char* fileName = validateFileName();
        if (fileAlreadyExists(fileName)) {
            printf("File already exists!\n");
        }
    } while (fileAlreadyExists(fileName));
    return fileName;
}
char* getExistingFileName() {
    char* fileName;
    do{
        char* fileName = validateFileName();
        if (!fileAlreadyExists(fileName)) {
            printf("File does not exist!\n");
        }
    } while (!fileAlreadyExists(fileName));
    return fileName;
}
char optionInRange(unsigned option) {
    return option >= 0 && option <= 10;
}
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
#endif