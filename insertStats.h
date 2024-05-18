#ifndef _STATS_H_
#define _STATS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "dequeue.h"
#include "malloque.h"
#include "panic.h"
#include <pthread.h>

typedef struct _accessedPage
{
    char* page;
    int numberOfAccess;
    struct _accessedPage* next;
} AccessedPageNode;

typedef struct _accessedPages
{
    AccessedPageNode* first;
} AccessedPagesList;

typedef struct {
    Queue* queue;
    char* logPath;
} insertStatsArgs;

void* insertStats(void* arg);

#endif