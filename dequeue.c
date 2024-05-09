#include "dequeue.h"
char* dequeue(LogQueue* queue) {
    pthread_mutex_lock(&queue->mutex);
    if (queue->head == NULL) {
        pthread_cond_wait(&queue->cond_consumer, &queue->mutex);
    }
    if (queue->head == NULL) {
        pthread_mutex_unlock(&queue->mutex);
        return NULL;
    }
    char* log = queue->head->log;
    Node* temp = queue->head;
    queue->head = queue->head->next;
    if (queue->head == NULL) {
        queue->tail = NULL;
    }
    free(temp);
    pthread_cond_signal(&queue->cond_producer);
    pthread_mutex_unlock(&queue->mutex);
    return log;
}