#include "insertLog.h"
extern char* _logPath; 
void* insertLog(void* arg) {
    struct insertLogArgs *a = arg;
    char* logPath = a->logPath;
    Queue* queue = a->queue;
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
    }
    pthread_exit(NULL);
}