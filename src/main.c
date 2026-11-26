#include <stdio.h>

#include "core/common.h"
#include "mem/arena.h"
#include "mem/pool.h"
#include "mem/mem_stats.h"

typedef struct DemoNode {
    int   id;
    float value;
    struct DemoNode *next;
} DemoNode;

int main(void)
{
    printf("sdfr %s — программный SDF-рендерер здания (CPU, C + NASM)\n", SDFR_VERSION);

    Arena arena;
    if (!arena_init(&arena, MIB(64), "persistent"))
        die("не удалось выделить арену");

    Pool nodes;
    pool_init(&nodes, &arena, sizeof(DemoNode), 1024, "nodes");

    size_t heap_before = mem_heap_calls();

    DemoNode *head = NULL;
    for (int i = 0; i < 1000; i++) {
        DemoNode *n = pool_alloc(&nodes);
        n->id = i;
        n->value = (float)i * 0.5f;
        n->next = head;
        head = n;
    }
    printf("пул '%s': занято %zu из %zu слотов (слот %zu байт)\n",
           nodes.name, nodes.in_use, nodes.capacity, nodes.slot_size);

    while (head) {
        DemoNode *next = head->next;
        pool_free(&nodes, head);
        head = next;
    }
    printf("после освобождения: занято %zu, пик %zu\n", nodes.in_use, nodes.peak);

    printf("вызовов malloc/calloc/realloc за демо: %zu\n", mem_heap_calls() - heap_before);
    printf("арена '%s': занято %zu байт\n", arena.name, arena.used);

    arena_destroy(&arena);
    return 0;
}
