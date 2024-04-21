#include <Windows.h>
#include "wox_types.h"
#include <stdio.h>
#define MAX_FIELD_LENGTH 1024
#define MAX_ROWS 5000

int reader_pointnames_paramnames(char filepath[], REQUEST_POINTPARAMNAMES rp[]) {
    char line[MAX_FIELD_LENGTH];
    char *token;
    int index = 0;
    FILE* pointnamesparamnamescsv = fopen(filepath, "r");
    if (pointnamesparamnamescsv == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", filepath);
        return -1;
    }
    while (fgets(line, sizeof(line), pointnamesparamnamescsv) != NULL && index < MAX_ROWS) {
        token = strtok(line, ";");
        token = strtok(NULL, ";");
        if (token != NULL) {
            size_t len = strlen(token);
            rp[index].pointname = malloc(len + 1);
            if (rp[index].pointname == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                fclose(pointnamesparamnamescsv);
                return -1;
            }
            strncpy(rp[index].pointname, token, len);
            rp[index].pointname[len] = '\0'; 
        }
        token = strtok(NULL, ";");
        if (token != NULL) {
            size_t len = strlen(token);
            rp[index].paramname = malloc(len + 1);
            if (rp[index].paramname == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                fclose(pointnamesparamnamescsv);
                return -1;
            }
            strncpy(rp[index].paramname, token, len);
            rp[index].paramname[len] = '\0'; 
        }
        index++;
    }
    fclose(pointnamesparamnamescsv);
    return index; 
}

int reader_pointparamnums(char filepath[], POINTPARAMNUM ppn[]) {
    char line[MAX_FIELD_LENGTH];
    char *token;
    int index = 0;
    FILE* file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", filepath);
        return -1;
    }
    while (fgets(line, sizeof(line), file) != NULL && index < MAX_ROWS) {
        token = strtok(line, ";");

		token = strtok(NULL, ";");

        if (token != NULL) {
            ppn[index].pointnum = strtoul(token, NULL, 10);
        }

        token = strtok(NULL, ";");
        if (token != NULL) {
            ppn[index].paramnum = strtoul(token, NULL, 10);
        }
        index++;
    }
    fclose(file);
    return index; 
}