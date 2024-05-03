#ifndef _HANDLE_DATA_H_
#define _HANDLE_DATA_H_
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#define B_HEAD_MAX_SIZE 4096
#define B_FILE_MAX_SIZE 4096
#define EIGHT_KB 1024 * 8
void* handleData(void* args);
struct handleDataArgs {
    int socket;
    int threadNo;
    char* filesLocation;
};
#endif