#include "debug.h"

/*
 * Show debug message. If SHOW_DEBUG_MESSAGES is not
 * defined the debug function is replaced by an empty
 * function.
 */



void debug(Queue* queue, const char* message, ...) {
    if (isVerbose) {
        va_list args;
        va_start(args, message);
        char* log = malloque(80192);
        vsprintf(log, message, args);
        strcat(log, "\n");
        enqueue(queue, log);
        va_end(args);
    }
}
