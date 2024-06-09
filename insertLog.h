#ifndef _LOGGER_H_
#define _LOGGER_H_
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "dequeue.h"
#include "utils.h"
#include "debug.h"
void* insertLog(void* arg);
typedef struct {
    Queue* queue;
    char* logPath;
} insertLogArgs;
#endif