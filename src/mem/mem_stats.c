#include "mem/mem_stats.h"

static size_t g_heap_calls;

void *__real_malloc(size_t n);
void *__real_calloc(size_t n, size_t s);
void *__real_realloc(void *p, size_t n);

void *__wrap_malloc(size_t n)
{
    g_heap_calls++;
    return __real_malloc(n);
}

void *__wrap_calloc(size_t n, size_t s)
{
    g_heap_calls++;
    return __real_calloc(n, s);
}

void *__wrap_realloc(void *p, size_t n)
{
    g_heap_calls++;
    return __real_realloc(p, n);
}

size_t mem_heap_calls(void)
{
    return g_heap_calls;
}
