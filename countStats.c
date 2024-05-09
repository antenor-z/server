#include "countStats.h"

void updateAccessCount(PageAccess pages[], int *numPages, char *pageName) {
    int i;
    for (i = 0; i < *numPages; i++) {
        if (strcmp(pages[i].name, pageName) == 0) {
            pages[i].count++;
            return;
        }
    }

    strcpy(pages[*numPages].name, pageName);
    pages[*numPages].count = 1;
    (*numPages)++;
}

void countStats(char* statsPath, char* outputPath) {
    FILE *inputFile, *outputFile;
    char page[MAX_PAGE_NAME_LENGTH];
    PageAccess pages[MAX_PAGES];
    int numPages = 0;

    inputFile = fopen(statsPath, "r");
    if (inputFile == NULL) {
        panic(1, "Error opening input file.");
        return;
    }

    while (fscanf(inputFile, "%s", page) != EOF) {
        updateAccessCount(pages, &numPages, page);
    }

    fclose(inputFile);

    outputFile = fopen(outputPath, "w");
    if (outputFile == NULL) {
        panic(1, "Error opening output file.");
        return;
    }

    for (int i = 0; i < numPages; i++) {
        fprintf(outputFile, "%s: %d\n", pages[i].name, pages[i].count);
    }

    fclose(outputFile);
    // remove(statsPath);
}
