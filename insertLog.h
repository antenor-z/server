#ifndef _LOGGER_H_
#define _LOGGER_H_
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "dequeue.h"
#include "panic.h"
void* insertLog(void* arg);
struct insertLogArgs {
    LogQueue* queue;
    char* logPath;
};
#endif