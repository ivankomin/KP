#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include "validation.h"

int main(){
    //forceWorkDir();
    char option = 0;
    unsigned recordNumber = 0;
    unsigned recordCount = 0;
    char* fileName = "a.csv"; 
    do {
        system("cls");
        printf("This is a file manager program. Create, read, edit and delete files and records.\n");
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
                readFile(fileName); 
                break;
            case '2':
                deleteFile(fileName);
                break;
            case '3':
                system("cls");
                writeRecord(fileName);
                break;
            case '4':
                system("cls");
                recordCount = countAllRecords(fileName);
                recordNumber = validateIntInput("Enter record number: ", 1, recordCount, "Invalid record position.\n");
                readRecord(fileName, recordNumber);
                break;
            case '5':
                system("cls");
                recordCount = countAllRecords(fileName);
                recordNumber = validateIntInput("Enter record number: ", 1, recordCount, "Invalid record position.\n");
                editRecord(fileName, recordNumber); 
                break;
            case '6':
                system("cls");
                char sortBy = validateChars("Which field do you want to sort by? (1 - region, 2 - area, 3 - population): ", sortByInRange, "Invalid input!\n");
                char sortOrder = validateChars("In what order do you want to sort? (1 - ascending, 2 - descending): ", sortOrderInRange, "Invalid input!\n");
                sortRecords(fileName, sortOrder, sortBy);  
                break;
            case '7':
                system("cls");    
                recordCount = countAllRecords(fileName);
                unsigned position = validateIntInput("Enter the insert position: ", 1, recordCount+1, "Invalid insert position.\n");
                insertRecord(fileName, position);
                break;
            case '8':
                system("cls");
                recordCount = countAllRecords(fileName);
                recordNumber = validateIntInput("Enter record number: ", 1, recordCount, "Invalid record position.\n");
                deleteRecord(fileName, recordNumber);
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