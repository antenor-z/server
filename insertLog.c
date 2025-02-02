#include "insertLog.h"

/*
 * Consumes the queue and inserts log in file
 */
void* insertLog(void* arg) {
    insertLogArgs *a = arg;
    char* logPath = a->logPath;
    Queue* queue = a->queue;
    debug(queue, "Insert log consumer created: %s", logPath);
    while (1) {
        FILE* file = fopen(logPath, "a");
        if (file == NULL) {
            panic(1, "Error opening file");
            pthread_exit(NULL);
        }
        char* log = dequeue(queue);
        if (log != NULL) {
            fputs(log, file);
            free(log);
        }
        // else {
        //     /* Exit if the queue is empty */
        //     break;
        // }
        fclose(file);
        pthread_testcancel();
    }
    pthread_exit(NULL);
}