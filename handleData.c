#include "handleData.h"
#include "panic.h"
#include <string.h>
#include <stdbool.h>

void handleData(int socket) {
    int n;
    char bufferHeaders[B_HEAD_MAX_SIZE];
    char bufferFile[B_FILE_MAX_SIZE];
    char* headers = malloc(1000);
    bool emptyResponse = false;
    
    while((n = read(socket, bufferHeaders, sizeof bufferHeaders)) > 0) {
        printf("Received %d bytes\n", (int)n);
        puts("@@@@");
        puts(bufferHeaders);
        puts("@@@@");
        if (bufferHeaders[n-1] == '\n') break;
    }

    // Open the desired file
    FILE *fp = fopen("doc/x.html", "r");
    if (fp == NULL) {
        strcpy(headers, "HTTP/1.1 404 Not Found\n"
        "Server: A4-Server\n"
        "Content-Type: text/html\n"
        "\n"
        "\0");
        emptyResponse = true;
    }
    else {
        strcpy(headers, "HTTP/1.1 200 OK\n"
        "Server: A4-Server\n"
        "Content-Type: text/html\n"
        "\n"
        "\0");
    }

    write(socket, headers, strlen(headers));

    if (!emptyResponse) {
        while ((n = fread(bufferFile, 1, B_FILE_MAX_SIZE, fp)) > 0) {
            write(socket, bufferFile, n);
        }
        fclose(fp);
    }

    puts("Conection terminated\n");
    close(socket);
    free(headers);
}