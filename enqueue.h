#ifndef _ENQUEUE_H_
#define _ENQUEUE_H_
#include "queue.h"
#include "malloque.h"
#include "debug.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


void enqueue(Queue* queue, void* item, ...);

#endif
