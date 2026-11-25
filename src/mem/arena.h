#ifndef SDFR_ARENA_H
#define SDFR_ARENA_H

#include "core/common.h"

typedef struct Arena {
    uint8_t    *base;
    size_t      cap;
    size_t      used;
    size_t      peak;
    size_t      allocs;
    const char *name;
} Arena;

bool   arena_init(Arena *a, size_t cap, const char *name);
void   arena_destroy(Arena *a);
void  *arena_alloc(Arena *a, size_t size, size_t align);
void  *arena_alloc_zero(Arena *a, size_t size, size_t align);
size_t arena_mark(const Arena *a);
void   arena_reset_to(Arena *a, size_t mark);
void   arena_reset(Arena *a);

#define ARENA_NEW(a, T)      ((T *)arena_alloc_zero((a), sizeof(T), _Alignof(T)))
#define ARENA_ARRAY(a, T, n) ((T *)arena_alloc((a), sizeof(T) * (size_t)(n), _Alignof(T)))

#endif
