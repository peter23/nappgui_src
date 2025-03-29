/*
 * NAppGUI Cross-platform C SDK
 * 2015-2025 Francisco Garcia Collado
 * MIT Licence
 * https://nappgui.com/en/legal/license.html
 *
 * File: heap.h
 * https://nappgui.com/en/core/heap.html
 *
 */

/* Fast memory allocator and auditor */

#include "core.hxx"

#include <malloc.h>

__EXTERN_C

/*_core_api void heap_start_mt(void);

_core_api void heap_end_mt(void);

_core_api void heap_verbose(const bool_t verbose);

_core_api void heap_stats(const bool_t stats);

_core_api bool_t heap_leaks(void);

_core_api byte_t *heap_malloc_imp(const uint32_t size, const char_t *name, const bool_t equal_sized);

_core_api byte_t *heap_calloc_imp(const uint32_t size, const char_t *name, const bool_t equal_sized);

_core_api byte_t *heap_realloc(byte_t *mem, const uint32_t size, const uint32_t new_size, const char_t *name);

_core_api byte_t *heap_aligned_malloc_imp(const uint32_t size, const uint32_t align, const char_t *name, const bool_t equal_sized);

_core_api byte_t *heap_aligned_calloc_imp(const uint32_t size, const uint32_t align, const char_t *name, const bool_t equal_sized);

_core_api byte_t *heap_aligned_realloc(byte_t *mem, const uint32_t size, const uint32_t new_size, const uint32_t align, const char_t *name);

_core_api void heap_free(byte_t **mem, const uint32_t size, const char_t *name);

_core_api void heap_auditor_add(const char_t *name);

_core_api void heap_auditor_delete(const char_t *name);*/

#define heap_start_mt(...)

#define heap_end_mt(...)

#define heap_verbose(...)

#define heap_stats(...)

#define heap_leaks(...)

#define heap_malloc_imp(size, name, equal_sized) \
        cast(malloc(size), byte_t)

#define heap_calloc_imp(size, name, equal_sized) \
        cast(calloc(1, size), byte_t)

#define heap_realloc(mem, size, new_size, name) \
        cast(realloc(cast(mem, void), new_size), byte_t)

#define heap_aligned_malloc_imp(size, align, name, equal_sized) \
        cast(_aligned_malloc(align, size), byte_t)

_core_api byte_t *heap_aligned_calloc_imp(const uint32_t size, const uint32_t align, const char_t *name, const bool_t equal_sized);

#define heap_aligned_realloc(mem, size, new_size, align, name) \
        cast(_aligned_realloc(cast(mem, void), align, new_size, size, 0), byte_t)

#define heap_free(mem, size, name) \
        (free(cast(*mem, void)), *mem = NULL)

#define heap_auditor_add(...)

#define heap_auditor_delete(...)

__END_C

#define heap_malloc(size, name) \
    heap_malloc_imp(size, name, FALSE)

#define heap_calloc(size, name) \
    heap_calloc_imp(size, name, FALSE)

#define heap_aligned_malloc(size, align, name) \
    heap_aligned_malloc_imp(size, align, name, FALSE)

#define heap_aligned_calloc(size, align, name) \
    heap_aligned_calloc_imp(size, align, name, FALSE)

#define heap_new(type) \
    cast(heap_malloc_imp((uint32_t)sizeof(type), cast_const(#type, char_t), TRUE), type)

#define heap_new0(type) \
    cast(heap_calloc_imp((uint32_t)sizeof(type), cast_const(#type, char_t), TRUE), type)

#define heap_new_n(n, type) \
    cast(heap_malloc_imp(((uint32_t)sizeof(type) * (uint32_t)(n)), cast_const(#type HEAPARR, char_t), FALSE), type)

#define heap_new_n0(n, type) \
    cast(heap_calloc_imp(((uint32_t)sizeof(type) * (uint32_t)(n)), cast_const(#type HEAPARR, char_t), FALSE), type)

#define heap_realloc_n(mem, size, new_size, type) \
    ((void)(cast(mem, type) == mem), \
     cast(heap_realloc(cast(mem, byte_t), ((size) * (uint32_t)sizeof(type)), ((new_size) * (uint32_t)sizeof(type)), cast_const(#type HEAPARR, char_t)), type))

#define heap_delete(obj, type) \
    ((void)((obj) == dcast(obj, type)), \
     heap_free(dcast(obj, byte_t), (uint32_t)sizeof(type), cast_const(#type, char_t)))

#define heap_delete_n(objs, n, type) \
    ((void)((objs) == dcast(objs, type)), \
     heap_free(dcast(objs, byte_t), ((uint32_t)sizeof(type) * (uint32_t)(n)), cast_const(#type HEAPARR, char_t)))
