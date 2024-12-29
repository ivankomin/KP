#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "func.h"
#include "validation.h"

int main(){
    //forceWorkDir();
    char option = 0;
    unsigned recordNumber = 0;
    unsigned recordCount = 0;
    char* fileName = NULL;
    printf("This is a file manager program. Create, read, edit and delete files and records. This program uses only CSV files.\n");
    listFiles(".", ".csv");
    fileName = validateFileName(getExistingFileName, "No such file or ivalid file signature!\n");
    printf("You have chosen file: %s\n", fileName); 
    sleep(1);
    do {
        system("cls");
        printMenu();
        option = validateChars("Enter your option: ",optionInRange, "Invalid input!\n");
        switch (option) {
            case CREATE_FILE:
                system("cls");
                fileName = validateFileName(getNewFileName, "File already exists!\n");
                createFile(fileName); 
                break;
            case READ_FILE:
                system("cls");
                readFile(fileName); 
                break;
            case DELETE_FILE:
                system("cls");
                deleteFile(fileName);
                break;
            case CREATE_RECORD:
                system("cls");
                writeRecord(fileName);
                break;
            case READ_RECORD:
                system("cls");
                recordCount = countAllRecords(fileName);
                recordNumber = validateIntInput("Enter record number: ", 1, recordCount, "Invalid record position.\n");
                readRecord(fileName, recordNumber);
                break;
            case EDIT_RECORD:
                system("cls");
                recordCount = countAllRecords(fileName);
                recordNumber = validateIntInput("Enter record number: ", 1, recordCount, "Invalid record position.\n");
                editRecord(fileName, recordNumber); 
                break;
            case SORT_RECORDS:
                system("cls");
                char sortBy = validateChars("Which field do you want to sort by? (1 - region, 2 - area, 3 - population): ", sortByInRange, "Invalid input!\n");
                char sortOrder = validateChars("In what order do you want to sort? (1 - ascending, 2 - descending): ", sortOrderInRange, "Invalid input!\n");
                sortRecords(fileName, sortOrder, sortBy);  
                break;
            case INSERT_RECORD:
                system("cls");    
                recordCount = countAllRecords(fileName);
                unsigned position = validateIntInput("Enter the insert position: ", 1, recordCount+1, "Invalid insert position.\n");
                insertRecord(fileName, position);
                break;
            case DELETE_RECORD:
                system("cls");
                recordCount = countAllRecords(fileName);
                recordNumber = validateIntInput("Enter record number: ", 1, recordCount, "Invalid record position.\n");
                deleteRecord(fileName, recordNumber);
                break;
            case EXIT:
                break;          
            default:
                printf("Something went wrong...\n");
                break;
        }
    }while (option != EXIT);
    return 0;
}