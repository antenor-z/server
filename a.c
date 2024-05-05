#include <stdio.h>
#include <stdlib.h>
#include "dequeue.h"
#include "enqueue.h"
#include "queue.h"

#define NUM_THREADS 21

// Producer function
void* producer(void* arg) {
    LogQueue* queue = (LogQueue*)arg;
    // Create logs and enqueue them
    for (int i = 0; i < 10; i++) {
        
        sleep(1); // Simulate work
    }
    pthread_exit(NULL);
}

// Consumer function


int main() {
    pthread_t threads[NUM_THREADS];
    LogQueue queue = { .head = NULL, .tail = NULL, .mutex = PTHREAD_MUTEX_INITIALIZER,
                       .cond_producer = PTHREAD_COND_INITIALIZER, .cond_consumer = PTHREAD_COND_INITIALIZER };

    // Create producer threads
    for (int i = 0; i < NUM_THREADS - 1; i++) {
        pthread_create(&threads[i], NULL, producer, (void*)&queue);
    }

    // Create consumer thread
    pthread_create(&threads[NUM_THREADS - 1], NULL, consumer, (void*)&queue);

    // Join all threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}



