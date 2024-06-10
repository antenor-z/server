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
#include <fcntl.h>
#include "handleData.h"
#include "insertStats.h"
#include "enqueue.h"
#include "dequeue.h"
#include "queue.h"
#include "utils.h"
#include "debug.h"
#include "insertLog.h"

#define LINE_1 " ██████   ██    ██ "
#define LINE_2 "██    ██  ██    ██ "
#define LINE_3 "████████  ████████ "
#define LINE_4 "██    ██        ██ "
#define LINE_5 "██    ██        ██ "
#define LINE_6 "                   "
#define EVER ;;
#define MAXLISTEN 257
#define NUM_THREADS 1000
#define INVALID_THREAD 0xABABAC

typedef union {
struct sockaddr_in cliente4;
struct sockaddr_in6 cliente6;
} tEndereco;


int server(char* port, char* filesLocation, char* logPath, char* statsPath, bool background);
#endif