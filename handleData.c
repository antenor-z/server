#include "handleData.h"
#include "panic.h"

void handleData(int socket) {
    int n;
    char bufferHeaders[B_HEAD_MAX_SIZE];
    char bufferFile[B_FILE_MAX_SIZE];
    char* headers = malloc(1000);
    bool emptyResponse = false;
    
    while((n = read(socket, bufferHeaders, sizeof bufferHeaders)) > 0) {
        printf("[  Server  ] Received %d bytes\n", (int)n);
        puts("[  Client headers  ]");
        puts(bufferHeaders);
        puts("[  End Client headers  ]");
        if (bufferHeaders[n-1] == '\n') break;
    }
    bufferHeaders[n-1] = '\0';

    char* path = strtok(bufferHeaders, " ");
    path = strtok(NULL, " ");
    char* absPath = malloc(B_FILE_MAX_SIZE);
    realpath(path, absPath);
    printf("[  Server  ] Requested path: '%s'\n", absPath);

    FILE *fp = fopen(absPath, "r");
    if (fp == NULL) {
        strcpy(headers, "HTTP/1.1 404 Not Found\n"
        "Server: A4-Server\n"
        "Content-Type: text/html\n"
        "\n"
        "\0");
        emptyResponse = true;
        puts("[  Server  ] HTTP/1.1 404 Not Found");
    }
    else {
        strcpy(headers, "HTTP/1.1 200 OK\n"
        "Server: A4-Server\n"
        "Content-Type: text/html\n"
        "\n"
        "\0");
        printf("[  Server  ] HTTP/1.1 202 OK %s\n", path);
    }

    write(socket, headers, strlen(headers));

    if (!emptyResponse) {
        while ((n = fread(bufferFile, 1, B_FILE_MAX_SIZE, fp)) > 0) {
            write(socket, bufferFile, n);
        }
        fclose(fp);
    }

    puts("[  Server  ] Conection terminated\n");
    close(socket);
    free(headers);
    free(absPath);
}