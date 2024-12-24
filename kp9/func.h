#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include "validation.h"
FILE *file;
typedef struct{
    char region[40];
    double area;
    double population;
} Record;
Record record;
void printMenu(){
    printf("Menu:\n"
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
           "  9 - Exit the program\n"
           "  10 - inspect FileHeader\n");
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
void readFile(char* fileName) {
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    //TODO make it so it actually prints out something meaningful
    char line[256]; 
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
    printf("File opened successfully!\n");
}
void deleteFile(char* fileName) {
    if (remove(fileName) == 0) {
        printf("File deleted successfully!\n");
    }
    else {
        printf("Error deleting file!\n");
    }
}

void createRecord(char *fileName) {
    file = fopen(fileName, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter the region: ");
    scanf("%s", record.region);
    printf("Enter the area: ");
    scanf("%lf", &record.area);
    printf("Enter the population: ");
    scanf("%lf", &record.population);
    fprintf(file, "Region: %s\nArea: %lf\nPopulation: %lf\n", record.region, record.area, record.population);
    fclose(file);

}
#endif