#ifndef _MAIN_H_
#define _MAIN_H_

#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include "help.h"
#include "panic.h"
#include "server.h"
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include "isValidPath.h"

#define MAX_PATH_SIZE 4096

extern bool isVerbose;

int main(int argc, char** argv);

#endif
