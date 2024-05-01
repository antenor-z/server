#include "panic.h"

void panic(int statusCode, const char* message, ...) {
    fprintf(stderr, "[  PANIC  ] ");
    va_list args;
    va_start(args, message);
    vfprintf(stderr, message, args);
    va_end(args);
    exit(statusCode);
}