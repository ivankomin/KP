#include <stdio.h>
#include "func.h"
#include "validation.h"
int main(){
    //forceWorkDir();
    printf("This is a file manager program. Create, read, edit and delete files and records.\n");
    printMenu();
    char option = 0;
    char* fileName = "a.csv"; 
    do {
        option = validateChars("Enter your option: ",optionInRange, "Invalid input!\n");
        switch (option) {
            case '0':
                fileName = validateFileName(getNewFileName, "File already exists!\n");
                createFile(fileName); 
                break;
            case '1':
                //fileName = validateFileName(getExistingFileName, "File does not exist!\n");
                readFile(fileName); 
                break;
            case '2':
                //fileName = validateFileName(getExistingFileName, "File does not exist!\n");
                deleteFile(fileName);
                break;
            case '3':
                //fileName = validateFileName(getExistingFileName, "File does not exist!\n");
                writeRecord(fileName);
                break;
            case '4':
                //fileName = validateFileName(getExistingFileName, "File does not exist!\n");
                unsigned recordNumber = validateIntInput("Enter record number: ", "Invalid input!\n");
                readRecord(fileName, recordNumber); 
                break;
            case '5':
                printf("option 5\n"); 
                break;
            case '6':
                printf("option 6\n"); 
                break;
            case '7':
                printf("option 7\n");
                break;
            case '8':
                printf("option 8\n");
                break;          
            default:
                printf("Something went wrong...\n");
                break;
        }
    }while (option != '9');
    return 0;
}