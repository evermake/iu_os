#include <stdlib.h>
#include <malloc.h>

// My own realloc implementation using malloc() and free()
void* realloc(void* ptr, size_t size) {
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    void* new_ptr = malloc(size);
    if (ptr == NULL) {
        return new_ptr;
    } else {
        size_t old_size = malloc_usable_size(ptr);

        if (size < old_size) {
            old_size = size;
        }

        for (int i = 0; i < old_size; i++) {
            ((char*)new_ptr)[i] = ((char*)ptr)[i];
        }
        free(ptr);
    }
    return new_ptr;
}
