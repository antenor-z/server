#include "enqueue.h"

void enqueue(Queue* queue, void* item, ...) {
    va_list args;
    va_start(args, item);

    va_list args_copy;
    va_copy(args_copy, args);
    int len = vsnprintf(NULL, 0, item, args_copy);
    va_end(args_copy);

    char* formatedItem = malloque(len + 1);
    vsprintf(formatedItem, item, args);
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
