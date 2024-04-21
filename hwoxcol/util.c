#include <windows.h>
#include <hscnapi.h>
#include <util.h>
#define MAX_FIELD_LENGTH 1000
#define MAX_ROWS 4000



int reader_pointnames_paramnames(char filepath[], REQUEST_PARAMS rp[]) {
    char line[MAX_FIELD_LENGTH];
    char *token;
    int index = 0;
    FILE* pointnamesparamnamescsv = fopen(filepath, "r");
    if (pointnamesparamnamescsv == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", filepath);
        return -1;
    }
    while (fgets(line, sizeof(line), pointnamesparamnamescsv) != NULL && index < MAX_ROWS) {
        // Use strtok to tokenize the line by semicolons
        token = strtok(line, ";");
        // Skip the first token (first column)
        // Move to the second token (second column)
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
            rp[index].pointname[len] = '\0'; // Ensure null termination
        }
        // Move to the third token (third column)
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
            rp[index].paramname[len] = '\0'; // Ensure null termination
        }
        index++;
    }
    fclose(pointnamesparamnamescsv);
    return index; // Return the number of items read
}