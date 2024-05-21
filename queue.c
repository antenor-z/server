#include "queue.h"
#include <stdlib.h>

void queueInit(Queue* queue) {
    queue->head = NULL;
    queue->tail = NULL;
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->cond_producer, NULL);
    pthread_cond_init(&queue->cond_consumer, NULL);
    debug("[  Queue  ] Creating queue %p\n", queue);
}
