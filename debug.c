#include "debug.h"

/*
 * Show debug message
 */

#ifdef SHOW_DEBUG_MESSAGES
void debug(const char* message, ...) {
    va_list args;
    va_start(args, message);
    vfprintf(stderr, message, args);
    fputs("\n", stderr);
    va_end(args);
}
#endif
#ifndef SHOW_DEBUG_MESSAGES
void debug(const char* message, ...) {}
#endif