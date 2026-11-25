#include "mem/arena.h"

#include <string.h>
#include <sys/mman.h>

bool arena_init(Arena *a, size_t cap, const char *name)
{
    memset(a, 0, sizeof(*a));
    cap = ALIGN_UP(cap, 4096);
    void *mem = mmap(NULL, cap, PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, -1, 0);
    if (mem == MAP_FAILED)
        return false;
    a->base = mem;
    a->cap  = cap;
    a->name = name;
    return true;
}

void arena_destroy(Arena *a)
{
    if (a->base)
        munmap(a->base, a->cap);
    memset(a, 0, sizeof(*a));
}

void *arena_alloc(Arena *a, size_t size, size_t align)
{
    if (align < 16)
        align = 16;
    size_t start = ALIGN_UP(a->used, align);
    if (start > a->cap || size > a->cap - start)
        die("арена '%s' переполнена: нужно %zu байт, свободно %zu",
            a->name, size, a->cap - a->used);
    a->used = start + size;
    if (a->used > a->peak)
        a->peak = a->used;
    a->allocs++;
    return a->base + start;
}

void *arena_alloc_zero(Arena *a, size_t size, size_t align)
{
    void *p = arena_alloc(a, size, align);
    memset(p, 0, size);
    return p;
}

size_t arena_mark(const Arena *a)
{
    return a->used;
}

void arena_reset_to(Arena *a, size_t mark)
{
    if (mark <= a->used)
        a->used = mark;
}

void arena_reset(Arena *a)
{
    a->used = 0;
}
