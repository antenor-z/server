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
        
        /* I tried to use malloque() here but valgrind with --leak-check=full complains
         * The maximum debug message is the HTTP header that 
         * (normally is less than) 4096 bytes */
        char log[4096];
        vsprintf(log, message, args);
        // strcat(log, "\n");
        enqueue(queue, log);
        va_end(args);
    }
}
