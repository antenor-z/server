#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include "handleData.h"

#define EVER ;;
#define MAXLISTEN 257

typedef union {
struct sockaddr_in cliente4;
struct sockaddr_in6 cliente6;
} tEndereco;


int server(char* port, char* filesLocation);