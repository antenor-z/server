#include "handleData.h"
#include "panic.h"
#include "malloque.h"

void handleData(int socket, char* filesLocation) {
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
        printf("[  Server  ] Received %d bytes\n", (int)n);
        puts("[  Client headers  ]");
        puts(bufferHeaders);
        puts("[  End Client headers  ]");
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
    
    printf("[  Server  ] Requested path: '%s'\n", pathWithBase);

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

    /* Returning file if it's needed */
    if (fileResponse) {
        while ((n = fread(bufferFile, 1, B_FILE_MAX_SIZE, fp)) > 0) {
            write(socket, bufferFile, n);
        }
        fclose(fp);
    }

    /* Clean */
    puts("[  Server  ] Conection terminated\n");
    close(socket);
    free(headers);
    free(pathWithBase);
    free(bufferHeaders);
    free(bufferFile);
}