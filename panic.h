#ifndef _PANIC_H_
#define _PANIC_H_
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void panic(int statusCode, const char* message, ...);
#endif