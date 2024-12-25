#include <stdio.h>
#include <unistd.h>
#include "func.h"
#include "validation.h"
int main(){
    if (chdir("C:/Users/ivank/projects/KP/kp9") != 0) {
        perror("chdir() failed");
        return 1;
    }

    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Forced Working Directory: %s\n", cwd);
    } else {
        perror("getcwd() error");
    }
    printf("This is a file manager program\n");
    unsigned option = 0;
    char* fileName; 
    printMenu();
    do {
        option = validateOption("Enter your option: ",optionInRange, "Invalid input!\n");
        switch (option) {
            case 0:
                fileName = validateFileName(getNewFileName, "File already exists!\n");
                createFile(fileName); 
                break;
            case 1:
                fileName = validateFileName(getExistingFileName, "File does not exist!\n");
                readFile(fileName); 
                break;
            case 2:
                fileName = validateFileName(getExistingFileName, "File does not exist!\n");
                deleteFile(fileName);
                break;
            case 3:
                fileName = validateFileName(getExistingFileName, "File does not exist!\n");
                createRecord(fileName);
                break;
            case 4:
                fileName = validateFileName(getExistingFileName, "File does not exist!\n");
                unsigned recordNumber = validateOption("Enter record number: ", optionInRange, "Invalid input!\n");
                readRecord(fileName, recordNumber); 
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