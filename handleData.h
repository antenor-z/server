#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#define B_HEAD_MAX_SIZE 4096
#define B_FILE_MAX_SIZE 4096
void handleData(int fd);