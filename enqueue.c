#include "enqueue.h"

void enqueue(Queue* queue, void* item) {
    pthread_mutex_lock(&queue->mutex);
    Node* newNode = (Node*)malloque(sizeof(Node));
    newNode->item = item;
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