#include "insertLog.h"
void* insertLog(void* arg) {
    LogQueue* queue = (LogQueue*)arg;
    FILE* file = fopen("logs.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        pthread_exit(NULL);
    }
    while (1) {
        char* log = dequeue(queue);
        if (log != NULL) {
            fputs(log, file);
            free(log);
        }
        // else {
        //     /* Exit if the queue is empty */
        //     break;
        // }
    }
    fclose(file);
    pthread_exit(NULL);
}