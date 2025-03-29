
#include "heap.h"

byte_t *heap_aligned_calloc_imp(const uint32_t size, const uint32_t align, const char_t *name, const bool_t equal_sized)
{
    byte_t *new_mem = heap_aligned_malloc(size, align, name, equal_sized);
    bmem_set_zero(new_mem, size);
    return new_mem;
}
