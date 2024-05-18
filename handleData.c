#include "handleData.h"

/*
 * Thread to process each TCP connection.
 * Get the required file.
 * if get is for "/", will return index.html
 * - Returns 200 OK if file exists.
 * - Return 404 Not Found if file not exists or thres a 
 * problem in opening the file.
 */
void* handleData(void* args) {
    /* Get args */
    struct handleDataArgs *a = args;
    int socket = a->socket;
    char* filesLocation = a->filesLocation;
    Queue* queue = a->queue;
    /* this queue used to history of pages accessed. It will be used
     * to make statistics later  */
    Queue* statsQueue = a->statsQueue;

    /* init */
    int n;
    char* bufferHeaders = malloque(B_HEAD_MAX_SIZE);
    char* bufferFile = malloque(B_FILE_MAX_SIZE);
    char* headers = malloque(EIGHT_KB);
    char* status = malloque(100);


    bool fileResponse = true;
    
    /* Getting headers */
    while((n = read(socket, bufferHeaders, B_HEAD_MAX_SIZE)) > 0) {
        debug("[  Thread %ld  ] Received %d bytes", pthread_self(), (int)n);
        debug("[  Thread %ld  ] ----- BEGIN CLIENT HEADERS -----", pthread_self());
        debug("%s", bufferHeaders);
        debug("[  Thread %ld  ] ----- END CLIENT HEADERS -----", pthread_self());
        if (bufferHeaders[n-1] == '\n' || n > B_HEAD_MAX_SIZE - 1) break;
    }
    bufferHeaders[n-1] = '\0';

    /* If the route is "/" answer with index.html */
    char* path = strtok(bufferHeaders, " ");
    path = strtok(NULL, " ");               // "/some/path.html"
    path += 1;                              // Discard first '/' "some/path.html"
    if (strcmp(path, "") == 0) {
        strcpy(path, "index.html");
    }

    /* Getting requested file path */
    char* pathWithBase = malloque(B_FILE_MAX_SIZE);
    strcat(pathWithBase, filesLocation);    // "base"
    strcat(pathWithBase, "/");              // "base/"
    strcat(pathWithBase, path);             // "base/some/path.html"

    /* Returning header */
    FILE *fp = fopen(pathWithBase, "r");
    if (fp == NULL) {
        strcpy(status, "HTTP/1.1 404 Not Found");
        strcpy(headers, NOT_FOUND_CONTENT);
        fileResponse = false;
    }
    else {
        strcpy(status, "HTTP/1.1 200 OK");
        strcpy(headers, OK_HEADERS);
    }

    write(socket, headers, strlen(headers));

    /* Returning file if it's needed */
    if (fileResponse) {
        while ((n = fread(bufferFile, 1, B_FILE_MAX_SIZE, fp)) > 0) {
            write(socket, bufferFile, n);
        }
        fclose(fp);
    }

    char* log = malloque(300);
    sprintf(log, "[ Thread %ld ] %s %s \"%s\"\n", pthread_self(), datetime(), status, pathWithBase);
    puts(log);
    enqueue(queue, log);
    char* p = malloque(300);
    sprintf(p, "%s", pathWithBase);
    enqueue(statsQueue, p);

    /* Clean */
    debug("[  Thread %ld  ] Conection terminated\n", pthread_self());
    close(socket);
    free(headers);
    free(pathWithBase);
    free(bufferHeaders);
    free(bufferFile);
    free(status);
    return NULL;
}