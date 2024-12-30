#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include <conio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include "validation.h"

#define MAX_REGION_LENGTH 3
#define MAX_BUFFER_SIZE 256
#define MAX_RECORDS 100

#define CREATE_FILE '0'
#define READ_FILE '1'
#define DELETE_FILE '2'
#define CREATE_RECORD '3'
#define READ_RECORD '4'
#define EDIT_RECORD '5'
#define SORT_RECORDS '6'
#define INSERT_RECORD '7'
#define DELETE_RECORD '8'
#define EXIT '9'

typedef struct{
    char region[MAX_REGION_LENGTH];
    double area;
    double population;
} Record;

Record record;
char line[MAX_BUFFER_SIZE];
FILE *file;

void printMenu(){
    printf("\nMenu:\n"
           "File mode:\n"
           "  %c - create file\n"
           "  %c - read file\n"
           "  %c - delete file\n"
           "\n"
           "Records mode:\n"
           "  %c - create record\n"
           "  %c - read record\n"
           "  %c - edit record\n"
           "  %c - sort records\n"
           "  %c - insert record\n"
           "  %c - delete record\n"
           "\n"
           "  %c - Exit the program\n\n", CREATE_FILE, READ_FILE, DELETE_FILE, CREATE_RECORD, READ_RECORD, EDIT_RECORD, SORT_RECORDS, INSERT_RECORD, DELETE_RECORD, EXIT);
}

void createFile(char* fileName) {
    file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error creating file!\n");
        return;
    }
    fclose(file);
    printf("File created successfully!\n");
    printf("Press any key to proceed to the menu");
    getch();
}

unsigned countAllRecords(const char* fileName) {
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    int recordCount = 0;
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%2[^,],%lf,%lf", record.region, &record.area, &record.population) == 3) {
            recordCount++;
        } else {
            printf("Error: Could not parse line: %s", line);
        }
    }
    fclose(file);
    printf("Number of records in the file: %d\n", recordCount);
    return recordCount;
}

//file functions start here
void readFile(const char* fileName) {
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int recordNumber = 1;
    printf("File contents:\n");

    while (fgets(line, sizeof(line), file)){
        if (sscanf(line, "%2[^,],%lf,%lf", record.region, &record.area, &record.population) == 3) {
            printf("%d)\n", recordNumber++);
            printf("Region: %s\n", record.region);
            printf("Area: %.2lf\n", record.area);
            printf("Population: %.2lf\n", record.population);
            printf("---\n");
        } else {
            printf("Error: Could not parse line: %s", line);
        }
    } 
    fclose(file);
    printf("Press any key to return to the menu");
    getch();
}

void deleteFile(char* fileName) {
    printf("Are you sure you want to delete the file %s?\n ", fileName);
    char choice = validateChars("(y/n): ", yesNo, "Invalid choice!\n");
    if (choice == 'n' || choice == 'N') {
        return;
    }
    if (remove(fileName) == 0) {
        printf("File deleted successfully!\n");
    }
    else {
        printf("Error deleting file!\n");
    }
    printf("Press any key to return to the menu");
    getch();
}

int listFiles(const char* directoryPath, const char* extension) {
    DIR* dir = opendir(directoryPath);
    if (dir == NULL) {
        printf("Error: Unable to open directory '%s'\n", directoryPath);
        return 0;
    }

    int fileCount = 0;
    struct dirent* entry;

    printf("Available files:\n");

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.' && strstr(entry->d_name, extension) != NULL) {
            printf("- %s\n", entry->d_name);
            fileCount++;
        }
    }
    closedir(dir);
    return fileCount;
}
//record functions start here
void writeRecord(const char* fileName) {
    file = fopen(fileName, "a"); 
    if (file == NULL) {
        printf("Error opening file");
        return;
    }
    char* input = validateStringInput("Enter region: ", isAlphabetic, "Region contains forbidden characters!\n");
    snprintf(record.region, MAX_REGION_LENGTH, "%s", input);
    record.area = validateDoubleInput("Enter area: ",isPositive, "Area must be positive!\n");
    record.population = validateDoubleInput("Enter population: ",isPositive, "Population must be positive!\n");

    fprintf(file, "%s,%.2lf,%.2lf\n", record.region, record.area, record.population);
    fclose(file);
    printf("Record saved successfully.\n");
    printf("Press any key to return to the menu");
    getch();
}

void readRecord(const char* fileName, int recordNumber) {
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file");
        return;
    }
    int currentRecord = 0;
    do{
        if (currentRecord == recordNumber) {
            if (sscanf(line, "%2[^,],%lf,%lf",record.region, &record.area, &record.population) == 3) {
                printf("Record %d:\n", recordNumber);
                printf("Region: %s\n", record.region);
                printf("Area: %.2lf\n", record.area);
                printf("Population: %.2lf\n", record.population);
            } else {
                printf("Error: Unable to parse record %d.\n", recordNumber);
            }
            fclose(file);
            printf("Press any key to return to the menu");
            getch();
            return;
        }
        currentRecord++;
    } while (fgets(line, sizeof(line), file));
    printf("Record %d not found.\n", recordNumber);
    fclose(file);
}

void editRecord(const char* fileName, int recordNumber) {
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return;
    }
    FILE* tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL) {
        printf("Error opening temporary file for writing!\n");
        fclose(file);
        return;
    }
    int currentRecord = 0;
    int recordFound = 0;

    while (fgets(line, sizeof(line), file)) {
        currentRecord++;
        if (currentRecord == recordNumber) {
            if (sscanf(line, "%2[^,],%lf,%lf", record.region, &record.area, &record.population) == 3) {
                printf("Editing record %d:\n", recordNumber);
                char* input = validateStringInput("Enter new region: ", isAlphabetic, "Region contains forbidden characters!\n");
                snprintf(record.region, MAX_REGION_LENGTH, "%s", input);
                record.area = validateDoubleInput("Enter new area: ", isPositive, "Area must be positive!\n");
                record.population = validateDoubleInput("Enter new population: ", isPositive, "Population must be positive!\n");
                fprintf(tempFile, "%s,%.2lf,%.2lf\n", record.region, record.area, record.population);
                recordFound = 1;
                continue;
            } else {
                printf("Error parsing record %d.\n", recordNumber);
            }
        }
        fputs(line, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    if (!recordFound) {
        printf("Record %d not found.\n", recordNumber);
        remove("temp.csv"); 
        return;
    }
    if (remove(fileName) != 0 || rename("temp.csv", fileName) != 0) {
        printf("Error replacing the original file!\n");
        return;
    }
    printf("Record %d edited successfully.\nNew record:\n", recordNumber);
    printf("Region: %s\n", record.region);
    printf("Area: %.2lf\n", record.area);
    printf("Population: %.2lf\n", record.population);
    printf("Press any key to return to the menu");
    getch();
}
void sortRecords(const char* fileName, char sortOrder, char sortBy) {
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    Record records[MAX_RECORDS];
    int recordCount = 0;

    while (fgets(line, sizeof(line), file)) {
        Record currentRecord;
        if (sscanf(line, "%2[^,],%lf,%lf", currentRecord.region, &currentRecord.area, &currentRecord.population) == 3) {
            records[recordCount++] = currentRecord;
        }
    }
    fclose(file);

    if (recordCount <= 1) {
        printf("The file contains less than 2 records.\n");
        return;
    }

    for (int i = 0; i < recordCount - 1; i++) {
        for (int j = 0; j < recordCount - i - 1; j++) {
            int shouldSwap = 0;

            switch (sortBy) {
                case '1': // Sort by Region
                    switch (sortOrder) {
                        case '1': // Ascending
                            shouldSwap = strcmp(records[j].region, records[j + 1].region) > 0;
                            break;
                        case '2': // Descending
                            shouldSwap = strcmp(records[j].region, records[j + 1].region) < 0;
                            break;
                        default:
                            printf("Something went wrong\n");
                            break;
                    }
                    break;

                case '2': // Sort by Area
                    switch (sortOrder) {
                        case '1': // Ascending
                            shouldSwap = records[j].area > records[j + 1].area;
                            break;
                        case '2': // Descending
                            shouldSwap = records[j].area < records[j + 1].area;
                            break;
                        default:
                            printf("Something went wrong.\n");
                            break;
                    }
                    break;

                case '3': // Sort by Population
                    switch (sortOrder) {
                        case '1': // Ascending
                            shouldSwap = records[j].population > records[j + 1].population;
                            break;
                        case '2': // Descending
                            shouldSwap = records[j].population < records[j + 1].population;
                            break;
                        default:
                            printf("Something went wrong.\n");
                            break;
                    }
                    break;

                default:
                    printf("Something went wrong.\n");
                    break;
            }

            if (shouldSwap) {
                Record temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
            }
        }
    }

    file = fopen(fileName, "w");
    if (!file) {
        printf("Error opening file for writing\n");
        return;
    }

    for (int i = 0; i < recordCount; i++) {
        fprintf(file, "%s,%.2lf,%.2lf\n", records[i].region, records[i].area, records[i].population);
    }
    fclose(file);

    printf("Records sorted successfully!\n New file contents:\n");
    readFile(fileName);
}
void insertRecord(const char* fileName, unsigned position) {
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    Record records[MAX_RECORDS];
    int recordCount = 0;

    while (fgets(line, sizeof(line), file)) {
        Record currentRecord;
        if (sscanf(line, "%2[^,],%lf,%lf", currentRecord.region, &currentRecord.area, &currentRecord.population) == 3) {
            records[recordCount++] = currentRecord;
        }
    }
    fclose(file);

    if (recordCount >= MAX_RECORDS) {
        printf("The file contains more than 100 records.\n");
        return;
    }

    char* input = validateStringInput("Enter new region: ", isAlphabetic, "Region contains forbidden characters!\n");
    snprintf(record.region, MAX_REGION_LENGTH, "%s", input);
    record.area = validateDoubleInput("Enter new area: ", isPositive, "Area must be positive!\n");
    record.population = validateDoubleInput("Enter new population: ", isPositive, "Population must be positive!\n");

    for (unsigned i = recordCount; i >= position; i--) {
        records[i] = records[i - 1];
    }

    records[position-1] = record;

    file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error opening file for writing\n");
        return;
    }

    for (int i = 0; i < recordCount + 1; i++) {
        fprintf(file, "%s,%.2lf,%.2lf\n", records[i].region, records[i].area, records[i].population);
    }

    fclose(file);

    printf("Record inserted successfully!\n New file contents:\n");
    readFile(fileName);
    printf("Press any key to return to the menu");
    getch();
}    

void deleteRecord(const char* fileName, int recordNumber) {
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    FILE* tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL) {
        printf("Error opening temporary file for writing!\n");
        fclose(file);
        return;
    }

    int currentRecord = 0;
    while (fgets(line, sizeof(line), file)) {
        if (currentRecord != recordNumber - 1) {
            fprintf(tempFile, "%s", line);
        }
        currentRecord++;
    }

    fclose(file);
    fclose(tempFile);

    if (remove(fileName) != 0 || rename("temp.csv", fileName) != 0) {
        printf("Error replacing the original file!\n");
        return;
    }
    printf("Record deleted successfully!\n New file contents:\n");
    readFile(fileName);
}
//end of record functions
void forceWorkDir(){
    if (chdir("C:/Users/ivank/projects/KP/kp9") != 0) {
        perror("chdir() failed"); 
        return;
    }
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Forced Working Directory: %s\n", cwd);
    } else {
        perror("getcwd() error");
    }
}
#endif