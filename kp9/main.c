#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include "validation.h"
int main(){
    forceWorkDir();
    printf("This is a file manager program. Create, read, edit and delete files and records.\n");
    char option = 0;
    unsigned recordNumber = 0;
    char* fileName = "a.csv"; 
    do {
        printMenu();
        option = validateChars("Enter your option: ",optionInRange, "Invalid input!\n");
        switch (option) {
            case '0':
                system("cls");
                fileName = validateFileName(getNewFileName, "File already exists!\n");
                createFile(fileName); 
                break;
            case '1':
                system("cls");
                //fileName = validateFileName(getExistingFileName, "File does not exist!\n");
                readFile(fileName); 
                break;
            case '2':
                //fileName = validateFileName(getExistingFileName, "File does not exist!\n");
                deleteFile(fileName);
                break;
            case '3':
                system("cls");
                //fileName = validateFileName(getExistingFileName, "File does not exist!\n");
                writeRecord(fileName);
                break;
            case '4':
                system("cls");
                //fileName = validateFileName(getExistingFileName, "File does not exist!\n");
                recordNumber = validateIntInput("Enter record number: ", "Invalid input!\n");
                readRecord(fileName, recordNumber); 
                break;
            case '5':
                recordNumber = validateIntInput("Enter record number: ", "Invalid input!\n");
                editRecord(fileName, recordNumber); 
                break;
            case '6':
                char sortBy = validateChars("Which field do you want to sort by? (1 - region, 2 - area, 3 - population): ", sortByInRange, "Invalid input!\n");
                char sortOrder = validateChars("In what order do you want to sort? (1 - ascending, 2 - descending): ", sortOrderInRange, "Invalid input!\n");
                break;
            case '7':
                printf("option 7\n");
                break;
            case '8':
                printf("option 8\n");
                break;
            case '9':
                printf("Exiting the program...\n");
                break;          
            default:
                printf("Something went wrong...\n");
                break;
        }
    }while (option != '9');
    return 0;
}