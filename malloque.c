#include "malloque.h"
#include "panic.h"

void *malloque(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        panic(1, "malloc failed");
    }
    return ptr;
}