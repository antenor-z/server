#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <pthread.h>

typedef struct Node {
    char* log;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    pthread_mutex_t mutex;
    pthread_cond_t cond_producer, cond_consumer;
} LogQueue;
#endif