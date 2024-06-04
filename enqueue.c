#include "enqueue.h"

void enqueue(Queue* queue, void* item, ...) {
    va_list args;
    va_start(args, item);
    char* formatedItem = malloque(strlen(item) * 5);
    vsprintf(formatedItem, item, args);
    va_end(args);

    Node* newNode = (Node*)malloque(sizeof(Node));
    newNode->item = formatedItem;
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
}
