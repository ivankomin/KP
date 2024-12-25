#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include "validation.h"
#include <unistd.h>
#define MAX_REGION_LENGTH 3
#define MAX_BUFFER_SIZE 256

char line[MAX_BUFFER_SIZE];
FILE *file;
typedef struct{
    char region[MAX_REGION_LENGTH];
    double area;
    double population;
} Record;
Record record;

void printMenu(){
    printf("\nMenu:\n"
           "File mode:\n"
           "  0 - create file\n"
           "  1 - read file\n"
           "  2 - delete file\n"
           "\n"
           "Records mode:\n"
           "  3 - create record\n"
           "  4 - read record\n"
           "  5 - edit record\n"
           "  6 - sort record\n"
           "  7 - paste record\n"
           "  8 - delete record\n"
           "\n"
           "  9 - Exit the program\n\n");
}

void createFile(char* fileName) {
    file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error creating file!\n");
        return;
    }
    fclose(file);
    printf("File created successfully!\n");
}

//some of the most dogshit code ive ever written starts somewhere round here :)
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
}

void deleteFile(char* fileName) {
    if (remove(fileName) == 0) {
        printf("File deleted successfully!\n");
    }
    else {
        printf("Error deleting file!\n");
    }
}

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
            return;
        }
        currentRecord++;
    } while (fgets(line, sizeof(line), file));

    printf("Record %d not found.\n", recordNumber);
    fclose(file);
}

//and ends approximately here

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