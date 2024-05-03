#include "handleData.h"
#include "panic.h"
#include "malloque.h"

void* handleData(void* args) {
    /* Get args */
    struct handleDataArgs *a = args;
    int socket = a->socket;
    char* filesLocation = a->filesLocation;
    int threadNo = a->threadNo;

    /* init */
    int n;
    char* bufferHeaders = malloque(B_HEAD_MAX_SIZE);
    char* bufferFile = malloque(B_FILE_MAX_SIZE);
    char* headers = malloque(EIGHT_KB);

    memset(bufferHeaders, '\0', B_HEAD_MAX_SIZE);
    memset(bufferFile, '\0', B_FILE_MAX_SIZE);
    memset(headers, '\0', EIGHT_KB);

    bool fileResponse = true;
    
    /* Getting headers */
    while((n = read(socket, bufferHeaders, B_HEAD_MAX_SIZE)) > 0) {
        printf("[  Thread %d  ] Received %d bytes\n", threadNo, (int)n);
        printf("[  Thread %d  ]  BEGIN CLIENT HEADERS \n", threadNo);
        puts(bufferHeaders);
        printf("[  Thread %d  ]  END CLIENT HEADERS \n", threadNo);
        if (bufferHeaders[n-1] == '\n' || n > B_HEAD_MAX_SIZE - 1) break;
    }
    bufferHeaders[n-1] = '\0';

    /* Getting requested file path */
    char* path = strtok(bufferHeaders, " "); 
    path = strtok(NULL, " ");               // "/some/path.html"
    path += 1;                              // Discard first '/' "some/path.html"
    char* pathWithBase = malloque(B_FILE_MAX_SIZE);
    strcpy(pathWithBase, filesLocation);    // "base"
    strcat(pathWithBase, "/");              // "base/"
    strcat(pathWithBase, path);             // "base/some/path.html"
    
    printf("[  Thread %d  ] Requested path: '%s'\n", threadNo, pathWithBase);

    /* Returning header */
    FILE *fp = fopen(pathWithBase, "r");
    if (fp == NULL) {
        strcpy(headers, "HTTP/1.1 404 Not Found\n"
        "Server: A4-Server\n"
        "Content-Type: text/html\n"
        "\n"
        "<html><head><meta charset='utf-8'><title>Não encontrado</title><body><h1>Erro 404</h1>Página não encontrada.<hr />A4-Server</body></html>"
        "\0");
        fileResponse = false;
        printf("[  Thread %d  ] HTTP/1.1 404 Not Found\n", threadNo);
    }
    else {
        strcpy(headers, "HTTP/1.1 200 OK\n"
        "Server: A4-Server\n"
        "Content-Type: text/html\n"
        "\n"
        "\0");
        printf("[  Thread %d  ] HTTP/1.1 202 OK %s\n", threadNo, path);
    }

    write(socket, headers, strlen(headers));

    /* Returning file if it's needed */
    if (fileResponse) {
        while ((n = fread(bufferFile, 1, B_FILE_MAX_SIZE, fp)) > 0) {
            write(socket, bufferFile, n);
        }
        fclose(fp);
    }

    /* Clean */
    printf("[  Thread %d  ] Conection terminated\n", threadNo);
    close(socket);
    free(headers);
    free(pathWithBase);
    free(bufferHeaders);
    free(bufferFile);
    return NULL;
}