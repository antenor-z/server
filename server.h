#ifndef _SERVER_H_
#define _SERVER_H_
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h> 
#include "handleData.h"
#include "stats.h"

#define EVER ;;
#define MAXLISTEN 257
#define NUM_THREADS 50

typedef union {
struct sockaddr_in cliente4;
struct sockaddr_in6 cliente6;
} tEndereco;


int server(char* port, char* filesLocation, char* logPath);
#endif