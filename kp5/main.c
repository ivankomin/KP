#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "validation.h"
#include "func.h"
#define MIN_RANGE 65
#define MAX_RANGE 122

int main(){
    printf("This program takes a number of strings of certain length from the user and sorts them alphabetically.\nThis program works only with latin characters.\n");
    do {
        unsigned numOfStrings = 0, lengthOfStrings = 0;
        char pick = 0;
        srand(time(NULL));

        numOfStrings = validateIntInput("Enter the number of strings (up to 100): ", "The number of strings must be between 0 and 100!\n");
        lengthOfStrings = validateIntInput("Enter the length of the strings (up to 100): ", "The length of the strings must be between 0 and 100!\n");

        char list[numOfStrings][lengthOfStrings + 1];
        char *addr [numOfStrings];

        pick = validateChars("Enter how you want to fill your array 'r' for random or 'm' for manual input: ", validateFormat, "Invalid input!\n");
        
        if (pick == 'm') {
            printf("Warning: your input must include only alphabetic characters (no whitespaces, digits etc.), any characters beyond user-specified length will be ignored\n");
            for (int i = 0; i < numOfStrings; i++) {
                do {
                    printf("Enter string %d: ", i + 1);
                    fgets(list[i], lengthOfStrings + 2, stdin);

                    if (list[i][strcspn(list[i], "\n")] != '\n') {
                        list[i][lengthOfStrings] = '\0';
                        while (getchar() != '\n'); 
                    }
                    else {
                        list[i][strcspn(list[i], "\n")] = '\0'; 
                    }
                    addr[i] = list[i];
                } while (!isAlphabetic(list[i]));
            }
        }
        
        else{
            for (int i = 0; i < numOfStrings; i++) {
                for (int j = 0; j < lengthOfStrings; j++) {
                    list[i][j] = generateRandomChar(MIN_RANGE, MAX_RANGE);
                }
                addr[i] = list[i];
                list[i][lengthOfStrings] = '\0';
                fflush(stdin);
            }
        }
        printf("Your array (unsorted): \n\n");
        for (int i = 0; i < numOfStrings; i++){
            printf("%d. -> %s\n", i+1,list[i]);
        }

        pick = validateChars("\nIn which order you want to sort your array ('a' for ascending or 'd' for descending): ", validateSortChoice, "Invalid input!\n");

        pick == 'a' 
                ? sortAsc(addr, numOfStrings) 
                : sortDesc(addr, numOfStrings);
        
        printf("\nYour array (sorted): \n\n");
        for (int i = 0; i < numOfStrings; i++){
            printf("%d. -> %s\n", i+1,addr[i]);
        }

        printf("\nPress '0' to quit or any other key to continue: ");
    } while (getchar() != 48);

    return 0;
}
