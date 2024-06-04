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
    // char* hostname = a->hostname;
    char* hostaddr = a->hostaddr;

    /* init */
    int n;
    char* bufferHeaders = malloque(B_HEAD_MAX_SIZE);
    char* bufferFile = malloque(B_FILE_MAX_SIZE);
    char* headers = malloque(EIGHT_KB);
    char* status = malloque(100);


    bool fileResponse = true;
    
    /* Getting headers */
    while((n = read(socket, bufferHeaders, B_HEAD_MAX_SIZE)) > 0) {
        debug(queue, "[  Thread %lx  ] Received %d bytes", pthread_self(), (int)n);
        debug(queue, "[  Thread %lx  ] ----- BEGIN CLIENT HEADERS -----", pthread_self());
        debug(queue, "%s", bufferHeaders);
        debug(queue, "[  Thread %lx  ] ----- END CLIENT HEADERS -----", pthread_self());
        if (bufferHeaders[n-1] == '\n' || n > B_HEAD_MAX_SIZE - 1) break;
    }
    bufferHeaders[n-1] = '\0';

    char path[1024] = {0};  
    if (sscanf(bufferHeaders, "%*s %1023s %*s", path) != 1) { 
        strcpy(path, "/");
    }

    /* If the route is "/" answer with index.html */
    if (strcmp(path, "/") == 0) {
        strcpy(path, "/index.html");
    }

    char* pathWithBase = malloque(strlen(path) + strlen(filesLocation) + 1);
    sprintf(pathWithBase, "%s%s", filesLocation, path);

    /* Ensure the pathWithBase is valid */
    if (strlen(pathWithBase) == 0 || strstr(pathWithBase, "..")) {
        strcpy(pathWithBase, "/index.html");  // Default to index.html on invalid paths
    }


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
        
        /* Get Content-Length */
        fseek(fp, 0L, SEEK_END);
        long int fsize = ftell(fp);
        fseek(fp, 0L, 0);

        char strContentLen[40];
        sprintf(strContentLen, "Content-Length: %ld\n", fsize);
        strcat(headers, strContentLen);

        /* Set file type */
        char strContentType[40];
        getFileType(pathWithBase, strContentType);
        strcat(headers, strContentType);

        strcat(headers, SEPARATOR);
    }

    write(socket, headers, strlen(headers));

    /* Returning file if it's needed */
    if (fileResponse) {
        while ((n = fread(bufferFile, 1, B_FILE_MAX_SIZE, fp)) > 0) {
            write(socket, bufferFile, n);
        }
        fclose(fp);
    }

    enqueue(queue, "[ Thread %lx ] %s (%s) %s \"%s\"\n", pthread_self(), datetime(), hostaddr, status, pathWithBase);
    enqueue(statsQueue, pathWithBase);

    /* Clean */
    debug(queue, "[  Thread %lx  ] Conection terminated", pthread_self());
    close(socket);
    free(headers);
    free(pathWithBase);
    free(bufferHeaders);
    free(bufferFile);
    free(status);
    return NULL;
}