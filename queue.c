#include "queue.h"

/*
 * Queue for multiple producers and one consumer
 */
void queueInit(Queue* queue) {
    queue->head = NULL;
    queue->tail = NULL;
    if (pthread_mutex_init(&queue->mutex, NULL) != 0) {
        panic(1, "Mutex init failed for queue %p", queue);
    }
    if (pthread_cond_init(&queue->cond_consumer, NULL) != 0) {
        panic(1, "Cond var init failed for queue %p", queue);
    }
}