#include "debug.h"

/*
 * Show debug message. If SHOW_DEBUG_MESSAGES is not
 * defined the debug function is replaced by an empty
 * function.
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