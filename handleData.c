#include "handleData.h"
#include "panic.h"
#include <string.h>

void handleData(int fd) {
    int n;
    char bufferHeaders[B_HEAD_MAX_SIZE];
    char bufferFile[B_FILE_MAX_SIZE];
    char* headers = "HTTP/1.1 200 OK\n"
    "Server: A4-Server\n"
    "Content-Type: text/html\n"
    "\n";
    
    while((n = read(fd, bufferHeaders, sizeof bufferHeaders)) > 0) {
        printf("Received %d bytes\n", (int)n);
        puts("@@@@");
        puts(bufferHeaders);
        puts("@@@@");
        if (bufferHeaders[n-1] == '\n') break;
    }

    // Open the desired file
    FILE *fp = fopen("index.html", "r");
    if (fp == NULL) {
        close(fd);
        panic(1, "Error while reading file.");
    }

    write(fd, headers, strlen(headers));
    while ((n = fread(bufferFile, 1, B_FILE_MAX_SIZE, fp)) > 0) {
        write(fd, bufferFile, n);
    }

    printf("Conexão terminada\n");
    close(fd);
}