#include "dequeue.h"

void* dequeue(Queue* queue) {
    pthread_mutex_lock(&queue->mutex);
    while (queue->head == NULL) {
        pthread_cond_wait(&queue->cond_consumer, &queue->mutex);
    }
    Node* temp = queue->head;
    void* item = temp->item;
    queue->head = queue->head->next;
    if (queue->head == NULL) {
        queue->tail = NULL;
    }
    free(temp);
    
    pthread_mutex_unlock(&queue->mutex);
    debug("Consumed on queue %p: element '%p' aka '%s'", queue, item, (char*) item);
    return item;
}
