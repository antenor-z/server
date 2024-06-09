#ifndef _UTILS_H_
#define _UTILS_H_
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

extern bool isVerbose;
extern bool breakLoop;

void bye();
bool isValidPath(char *path);
char* datetime();
void help();
void *malloque(size_t size);
void panic(int statusCode, const char* message, ...);
#endif