#include "enqueue.h"

void enqueue(Queue* queue, void* item) {
    Node* newNode = (Node*)malloque(sizeof(Node));
    newNode->item = item;
    newNode->next = NULL;

    pthread_mutex_lock(&queue->mutex);
    if (queue->tail == NULL) {
        queue->head = queue->tail = newNode;
    } else {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
    pthread_cond_signal(&queue->cond_consumer);
    pthread_mutex_unlock(&queue->mutex);
    debug("Inserted on queue %p: element '%p' aka '%s'", queue, item, (char*) item);
}
