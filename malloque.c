#include "malloque.h"
#include "panic.h"

/*
 * Safe malloc
 * Allocates and zeros the memory
 * If malloc is unsuccessful panic the program
 */
void *malloque(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        panic(1, "malloc failed");
    }
    memset(ptr, '\0', size);
    return ptr;
}