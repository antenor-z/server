#include "panic.h"

/*
 * If called, terminate the execution NOW. No clean-up of
 * threads, file pointers, socket will be done.
 */
void panic(int statusCode, const char* message, ...) {
    fprintf(stderr, "[  PANIC  ] ");
    va_list args;
    va_start(args, message);
    vfprintf(stderr, message, args);
    va_end(args);
    exit(statusCode);
}