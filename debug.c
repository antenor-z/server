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
        
        va_list args_copy;
        va_copy(args_copy, args);
        int len = vsnprintf(NULL, 0, message, args_copy);
        va_end(args_copy);

        char* log = malloque(len + 2); // Because of \n
        vsprintf(log, message, args);
        strcat(log, "\n");
        enqueue(queue, log);
        va_end(args);
    }
}
