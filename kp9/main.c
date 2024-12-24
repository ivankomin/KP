#include <stdio.h>
#include "func.h"
#include "validation.h"
int main(){
    printf("This is a file manager program\n");
    unsigned option = 0;
    char* fileName; 
    printMenu();
    do {
        option = validateOption("Enter your option: ",optionInRange, "Invalid input!\n");
        switch (option) {
            case 0:
                fileName = getNewFileName();
                createFile(fileName); 
                break;
            case 1:
                fileName = getExistingFileName();
                readFile(fileName); 
                break;
            case 2:
                fileName = getExistingFileName();
                deleteFile(fileName);
                break;
            case 3:
                fileName = getExistingFileName();
                createRecord(fileName); 
                break;
            case 4:
                printf("option 4\n"); 
                break;
            case 5:
                printf("option 5\n"); 
                break;
            case 6:
                printf("option 6\n"); 
                break;
            case 7:
                printf("option 7\n");
                break;
            case 8:
                printf("option 8\n");
                break;          
            case 9:
                printf("Exiting the program...\n");
                break;
            case 10:
                printf("option 10\n");
                break;
            default:
                printf("Something went wrong...\n");
                break;
        }
    }while (option != 9);
    return 0;
}