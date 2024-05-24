#include "dequeue.h"

void* dequeue(Queue* queue) {
    pthread_mutex_lock(&queue->mutex);
    while (queue->head == NULL) {
        pthread_cond_wait(&queue->cond_consumer, &queue->mutex);
    }
    void* item = queue->head->item;
    Node* temp = queue->head;
    queue->head = queue->head->next;
    if (queue->head == NULL) {
        queue->tail = NULL;
    }
    free(temp);
    pthread_mutex_unlock(&queue->mutex);
    debug("Consuming on queue %p: element '%s'", queue, (char*)item);
    return item;
}