#ifndef _DEBUG_H_
#define _DEBUG_H_
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "enqueue.h"
#include "malloque.h"

void debug(Queue* queue, const char* message, ...);

#endif
