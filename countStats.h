#ifndef _COUNT_STATS_H
#define _COUNT_STATS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "panic.h"

#define MAX_PAGES 1000
#define MAX_PAGE_NAME_LENGTH 4096

typedef struct {
    char name[MAX_PAGE_NAME_LENGTH];
    int count;
} PageAccess;

void countStats(char* statsPath, char* outputPath);

#endif