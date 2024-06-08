#include "malloque.h"

/*
 * Safe malloc
 * Allocates and zeros the memory
 * If malloc is unsuccessful panic the program, this way I don't need to
 * check for NULL ptr each time I allocate memory
 * I zero the memory to avoid buffer overflow even if I forget to null
 * terminate the string
 */
void *malloque(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        panic(1, "malloc failed");
    }
    memset(ptr, '\0', size);
    return ptr;
}