#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdlib.h>
#include <pthread.h>
#include "debug.h"
#include "panic.h"

typedef struct Node {
    void* item;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    pthread_mutex_t mutex;
    pthread_cond_t cond_consumer;
} Queue;

void queueInit(Queue* queue);

#endif