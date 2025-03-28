/*
 * NAppGUI Cross-platform C SDK
 * 2015-2025 Francisco Garcia Collado
 * MIT Licence
 * https://nappgui.com/en/legal/license.html
 *
 * File: bmem.h
 * https://nappgui.com/en/sewer/bmem.html
 *
 */

/* Operating System memory support */

#include "sewer.hxx"

__EXTERN_C

/*_sewer_api byte_t *bmem_aligned_malloc(const uint32_t size, const uint32_t align);

_sewer_api byte_t *bmem_aligned_realloc(byte_t *mem, const uint32_t size, const uint32_t new_size, const uint32_t align);

_sewer_api void bmem_free(byte_t *mem);*/

#include "rpmalloc.h"

#define bmem_aligned_malloc(size, align) \
        cast(rpaligned_alloc(align, size), byte_t)

#define bmem_aligned_realloc(mem, size, new_size, align) \
        cast(rpaligned_realloc(cast(mem, void), align, new_size, size, 0), byte_t)

#define bmem_free(mem) \
        rpfree(cast(mem, void))

_sewer_api void bmem_set1(byte_t *dest, const uint32_t size, const byte_t mask);

_sewer_api void bmem_set4(byte_t *dest, const uint32_t size, const byte_t *mask);

_sewer_api void bmem_set8(byte_t *dest, const uint32_t size, const byte_t *mask);

_sewer_api void bmem_set16(byte_t *dest, const uint32_t size, const byte_t *mask);

_sewer_api int bmem_cmp(const byte_t *mem1, const byte_t *mem2, const uint32_t size);

_sewer_api bool_t bmem_is_zero(const byte_t *mem, const uint32_t size);

_sewer_api void bmem_set_zero(byte_t *dest, const uint32_t size);

_sewer_api void bmem_copy(byte_t *dest, const byte_t *src, const uint32_t size);

_sewer_api void bmem_move(byte_t *dest, const byte_t *src, const uint32_t size);

_sewer_api bool_t bmem_overlaps(const byte_t *mem1, const byte_t *mem2, const uint32_t size1, const uint32_t size2);

_sewer_api void bmem_rev(byte_t *mem, const uint32_t size);

_sewer_api void bmem_rev2(byte_t *mem);

_sewer_api void bmem_rev4(byte_t *mem);

_sewer_api void bmem_rev8(byte_t *mem);

_sewer_api void bmem_revcopy(byte_t *dest, const byte_t *src, const uint32_t size);

_sewer_api void bmem_rev_elems_imp(byte_t *data, const uint32_t num_elems, const uint32_t elem_size);

_sewer_api void bmem_swap(byte_t *mem1, byte_t *mem2, const uint32_t size);

_sewer_api void bmem_shuffle(byte_t *mem, const uint32_t size, const uint32_t esize);

__END_C

#define bmem_malloc(size) \
    bmem_aligned_malloc((size), sizeof32(void *))

#define bmem_realloc(mem, size, new_size) \
    bmem_aligned_realloc((mem), (size), (new_size), sizeof32(void *))

#define bmem_set_u32(dest, n, value) \
    { \
        uint32_t ___value = (value); \
        bmem_set4(cast(dest, byte_t), (uint32_t)(sizeof32(uint32_t) * (n)), cast_const(&___value, byte_t)); \
    }

#define bmem_set_r32(dest, n, value) \
    { \
        real32_t ___value = (value); \
        bmem_set4(cast(dest, byte_t), (uint32_t)(sizeof32(real32_t) * (n)), cast_const(&___value, byte_t)); \
    }

#define bmem_zero(dest, type) \
    ((void)(cast(dest, type) == (dest)), \
     bmem_set_zero(cast(dest, byte_t), sizeof32(type)))

#define bmem_zero_n(dest, n, type) \
    ((void)(cast(dest, type) == (dest)), \
     bmem_set_zero(cast(dest, byte_t), n * sizeof32(type)))

#define bmem_copy_n(dest, src, n, type) \
    ((void)(cast(dest, type) == (dest)), \
     (void)(cast_const(src, type) == (src)), \
     bmem_copy(cast(dest, byte_t), cast_const(src, byte_t), (uint32_t)sizeof32(type) * (uint32_t)(n)))

#define bmem_rev_elems(elems, n, type) \
    ((void)(cast(elems, type) == (elems)), \
     bmem_rev_elems_imp(cast(elems, byte_t), (n), (uint32_t)sizeof32(type)))

#define bmem_swap_type(obj1, obj2, type) \
    ((void)(cast(obj1, type) == (obj1)), \
     (void)(cast(obj2, type) == (obj2)), \
     bmem_swap(cast(obj1, byte_t), cast(obj2, byte_t), (uint32_t)sizeof32(type)))

#define bmem_shuffle_n(arr, size, type) \
    ((void)(cast(arr, type) == arr), \
     bmem_shuffle(cast(arr, byte_t), size, sizeof32(type)))
