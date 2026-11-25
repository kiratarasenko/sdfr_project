#include <stdio.h>

#include "core/common.h"
#include "mem/arena.h"

int main(void)
{
    printf("sdfr %s — программный SDF-рендерер здания (CPU, C + NASM)\n", SDFR_VERSION);

    Arena arena;
    if (!arena_init(&arena, MIB(64), "demo"))
        die("не удалось выделить арену");

    size_t mark = arena_mark(&arena);
    float *a = arena_alloc(&arena, 1000 * sizeof(float), 32);
    double *b = ARENA_NEW(&arena, double);
    for (int i = 0; i < 1000; i++)
        a[i] = (float)i;
    *b = 42.0;
    printf("арена '%s': занято %zu байт, пик %zu, выделений %zu\n",
           arena.name, arena.used, arena.peak, arena.allocs);
    printf("адрес a выровнен на 32: %s\n", ((uintptr_t)a % 32 == 0) ? "да" : "нет");

    arena_reset_to(&arena, mark);
    printf("после отката: занято %zu байт, пик %zu\n", arena.used, arena.peak);

    arena_destroy(&arena);
    return 0;
}
