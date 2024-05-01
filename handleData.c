#include "handleData.h"
#include <string.h>

void handleData(int fd) {
    int n;
    char buffer[MAXTAMLINHA];
    char* headers = "HTTP/1.1 200 OK\n"
    "Server: A4-Server\n"
    "Content-Type: text/html\n"
    "\n";
    
    while((n = read(fd, buffer, sizeof buffer)) > 0) {
        printf("Servidor recebeu %d bytes\n", (int)n);
        puts(buffer);
        if (buffer[n-1] == '\n') break;
    }
    write(fd, headers, strlen(headers));
    printf("Conexão terminada\n");
    close(fd);
}