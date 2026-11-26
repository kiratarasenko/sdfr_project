#include "mem/pool.h"

#include <string.h>

void pool_init(Pool *p, Arena *backing, size_t elem_size, size_t capacity, const char *name)
{
    memset(p, 0, sizeof(*p));
    size_t slot = elem_size < sizeof(PoolSlot) ? sizeof(PoolSlot) : elem_size;
    p->slot_size = ALIGN_UP(slot, 16);
    p->capacity  = capacity;
    p->name      = name;
    p->mem       = arena_alloc(backing, p->slot_size * capacity, 64);
    pool_reset(p);
}

void pool_reset(Pool *p)
{
    p->free_list = NULL;
    for (size_t i = p->capacity; i-- > 0;) {
        PoolSlot *s = (PoolSlot *)(p->mem + i * p->slot_size);
        s->next = p->free_list;
        p->free_list = s;
    }
    p->in_use = 0;
}

void *pool_alloc(Pool *p)
{
    PoolSlot *s = p->free_list;
    if (!s)
        die("пул '%s' исчерпан (ёмкость %zu)", p->name, p->capacity);
    p->free_list = s->next;
    p->in_use++;
    if (p->in_use > p->peak)
        p->peak = p->in_use;
    memset(s, 0, p->slot_size);
    return s;
}

bool pool_owns(const Pool *p, const void *ptr)
{
    const uint8_t *b = ptr;
    if (b < p->mem || b >= p->mem + p->slot_size * p->capacity)
        return false;
    return (size_t)(b - p->mem) % p->slot_size == 0;
}

void pool_free(Pool *p, void *ptr)
{
    if (!ptr)
        return;
    if (!pool_owns(p, ptr))
        die("pool_free: указатель не принадлежит пулу '%s'", p->name);
    PoolSlot *s = ptr;
    s->next = p->free_list;
    p->free_list = s;
    p->in_use--;
}
