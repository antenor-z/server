#include "bye.h"

extern int breakLoop;
void bye(){
    breakLoop = true;
}