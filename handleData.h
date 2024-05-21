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
#include "datetime.h"
#include "panic.h"
#include "malloque.h"
#include "enqueue.h"
#include "debug.h"
#define B_HEAD_MAX_SIZE 4096
#define B_FILE_MAX_SIZE 2048
#define EIGHT_KB 1024 * 8
#define NOT_FOUND_CONTENT \
"HTTP/1.1 404 Not Found \
Server: A4-Server \
Content-Type: text/html \
\n\n \
<!DOCTYPE html> \
<html> \
    <head> \
        <meta charset='utf-8'> \
        <title>Não encontrado</title> \
    </head> \
    <body> \
        <h1>Erro 404</h1> \
        Página não encontrada. \
        <hr />A4-Server \
    </body> \
</html>"
#define OK_HEADERS \
"HTTP/1.1 200 OK\n \
Server: A4-Server\n \
Content-Type: text/html\n \
\n\n"

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