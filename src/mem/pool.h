#ifndef SDFR_POOL_H
#define SDFR_POOL_H

#include "mem/arena.h"

typedef struct PoolSlot {
    struct PoolSlot *next;
} PoolSlot;

typedef struct Pool {
    uint8_t    *mem;
    size_t      slot_size;
    size_t      capacity;
    size_t      in_use;
    size_t      peak;
    PoolSlot   *free_list;
    const char *name;
} Pool;

void  pool_init(Pool *p, Arena *backing, size_t elem_size, size_t capacity, const char *name);
void *pool_alloc(Pool *p);
void  pool_free(Pool *p, void *ptr);
void  pool_reset(Pool *p);
bool  pool_owns(const Pool *p, const void *ptr);

#endif
