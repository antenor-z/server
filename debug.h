#ifndef _DEBUG_H_
#define _DEBUG_H_
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define SHOW_DEBUG_MESSAGES
void debug(const char* message, ...);

#endif