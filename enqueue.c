#include "enqueue.h"
void enqueue(LogQueue* queue, char* log) {
    pthread_mutex_lock(&queue->mutex);
    Node* newNode = (Node*)malloque(sizeof(Node));
    newNode->log = log;
    newNode->next = NULL;
    if (queue->tail == NULL) {
        queue->head = queue->tail = newNode;
    } else {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
    pthread_cond_signal(&queue->cond_consumer);
    pthread_mutex_unlock(&queue->mutex);
}