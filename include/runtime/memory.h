#pragma once

#define HEAP_SIZE 16000

char *heap[HEAP_SIZE];

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * Marks this space as available.
     */
    void free(void *ptr);
    /**
     * Allocates `size` bytes onto the heap.
     */
    void *malloc(size_t size);
    /**
     * Reallocates `ptr`
     */
    void *realloc(void *ptr, size_t size);

#ifdef __cplusplus
}
#endif