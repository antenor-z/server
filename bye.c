#include "bye.h"
/*
 * Get out of main loop on SIGINT or SIGUSR1
 */
void bye(){
    breakLoop = true;
}