#include "bye.h"
/*
 * Get out of main loop on SIGINT or SIGUSR1
 */
extern int breakLoop;
void bye(){
    breakLoop = true;
}