#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void sortAsc(char **arr, int num){
    for (int i = 0; i < num - 1; i++) {
        for (int j = i + 1; j < num; j++) {
            if (strcmp(arr[i], arr[j]) > 0) {
                char *temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}
void sortDesc(char **arr, int num){
    for (int i = 0; i < num - 1; i++) {
        for (int j = i + 1; j < num; j++) {
            if (strcmp(arr[i], arr[j]) < 0) {
                char *temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}
char generateRandomChar(int min, int max) {
    char generatedChar;
    do{
        generatedChar = rand() % (max - min + 1) + min;
    } while (!isalpha(generatedChar));
    return generatedChar;
}

void printArray(char **array, int numOfStrings, const char *description) {
    printf("Your array (%s): \n\n", description);
    for (int i = 0; i < numOfStrings; i++) {
        printf("%d. -> %s\n", i + 1, array[i]);
    }
    printf("\n");
}
#endif