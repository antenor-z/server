#ifndef _HANDLE_DATA_H_
#define _HANDLE_DATA_H_
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include "queue.h"
#include "utils.h"
#include "enqueue.h"
#include "debug.h"
#include "getFileType.h"
#define B_HEAD_MAX_SIZE 4096
#define B_FILE_MAX_SIZE 2048
#define EIGHT_KB 1024 * 8
#define NOT_FOUND_CONTENT \
"HTTP/1.1 404 Not Found\n\
Server: A4-Server\n\
Content-Type: text/html\n\
Content-Length: 230\n\
\n\
<!DOCTYPE html>\n\
<html>\n\
    <head>\n\
        <meta charset='utf-8'>\n\
        <title>Não encontrado</title>\n\
    </head>\n\
    <body>\n\
        <h1>Erro 404</h1>\n\
        Página não encontrada.\n\
        <hr />A4-Server\n\
    </body>\n\
</html>\n"
#define OK_HEADERS \
"HTTP/1.1 200 OK\n\
Server: A4-Server\n"

void* handleData(void* args);
struct handleDataArgs {
    int socket;
    char* filesLocation;
    Queue* queue;
    Queue* statsQueue;
    char* hostname;
    char* hostaddr;
};
#endif
#define SEPARATOR "\n"