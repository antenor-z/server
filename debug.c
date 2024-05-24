#include "debug.h"

/*
 * Show debug message. If SHOW_DEBUG_MESSAGES is not
 * defined the debug function is replaced by an empty
 * function.
 */

extern bool isVerbose;

void debug(const char* message, ...) {
    if (isVerbose) {
        va_list args;
        va_start(args, message);
        vfprintf(stderr, message, args);
        fputs("\n", stderr);
        va_end(args);
    }
}
