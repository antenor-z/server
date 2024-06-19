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
    free(a);

    /* init */
    int n;
    char* bufferHeaders = malloque(HTTP_HEADER_MAX_SIZE + 1);
    char* bufferFile = malloque(CHUNK_SIZE);
    char* headers = malloque(HTTP_HEADER_MAX_SIZE);
    char* status = malloque(STATUS_MAX_SIZE);


    bool fileResponse = true;
    
    /* Getting headers */
    memset(bufferHeaders, '\0', HTTP_HEADER_MAX_SIZE);
    while((n = read(socket, bufferHeaders, HTTP_HEADER_MAX_SIZE)) > 0) {
        debug(queue, "[  Thread %lx  ] Received %d bytes", pthread_self(), (int)n);
        debug(queue, "[  Thread %lx  ] ----- BEGIN CLIENT HEADERS -----", pthread_self());
        debug(queue, "%s", bufferHeaders);
        debug(queue, "[  Thread %lx  ] ----- END CLIENT HEADERS -----", pthread_self());
        if (bufferHeaders[n-1] == '\n' || n > HTTP_HEADER_MAX_SIZE - 1) break;
    }
    bufferHeaders[HTTP_HEADER_MAX_SIZE] = '\0';

    char path[PATH_MAX] = {0};  
    if (sscanf(bufferHeaders, "%*s %1023s %*s", path) != 1) { 
        strcpy(path, "/");
    }

    char* pathWithBase = malloque(strlen(path) + strlen(filesLocation) + strlen("/index.html") + 1);
    sprintf(pathWithBase, "%s%s", filesLocation, path);

    /* Ensure the pathWithBase is valid */
    if (strlen(pathWithBase) == 0 || strstr(pathWithBase, "..")) {
        strcpy(pathWithBase, "/index.html");  // Default to index.html on invalid paths
    }

    /* If the route is a folder we want index.html */
    DIR *dir;
    if ((dir = opendir(pathWithBase)) != 0) {
        closedir(dir);
        enqueue(queue, "[  Thread %lx  ] A folder was requested, return index.html of that folder\n", pthread_self());
        strcat(pathWithBase, "/index.html");
    }


    /* Returning header */
    FILE *fp = fopen(pathWithBase, "r");
    if (fp == NULL) {
        debug(queue, "File was not found reponding with HTTP 404.");
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
        sprintf(strContentLen, "Content-Length: %ld", fsize);
        strcat(headers, strContentLen);
        strcat(headers, "\n");

        /* Set file type */
        char strContentType[40];
        getFileType(pathWithBase, strContentType);
        strcat(headers, strContentType);
        strcat(headers, "\n");

        strcat(headers, SEPARATOR);

        debug(queue, "[  Thread %lx  ] File '%s' was found", pthread_self(), pathWithBase);
        debug(queue, "[  Thread %lx  ] Size: %s", pthread_self(), strContentLen);
        debug(queue, "[  Thread %lx  ] MIME: %s", pthread_self(), strContentType);
    }

    write(socket, headers, strlen(headers));

    /* Returning file if it's needed */
    if (fileResponse) {
        while ((n = fread(bufferFile, 1, CHUNK_SIZE, fp)) > 0) {
            write(socket, bufferFile, n);
        }
        fclose(fp);
    }

    char* dt = datetime();
    enqueue(queue, "[  Thread %lx  ] %s (%s) %s \"%s\"\n", pthread_self(), dt, hostaddr, status, pathWithBase);
    free(dt);
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