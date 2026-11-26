#include <stdio.h>

#include "core/common.h"
#include "mem/arena.h"
#include "mem/mem_stats.h"
#include "math/vec3.h"
#include "gfx/framebuffer.h"

int main(void)
{
    printf("sdfr %s — программный SDF-рендерер здания (CPU, C + NASM)\n", SDFR_VERSION);

    Arena persistent;
    if (!arena_init(&persistent, MIB(64), "persistent"))
        die("не удалось выделить арену");

    Framebuffer fb;
    fb_init(&fb, &persistent, 320, 240);

    Vec3 top = v3(0.35f, 0.55f, 0.90f);
    Vec3 bottom = v3(0.95f, 0.85f, 0.70f);
    for (int y = 0; y < fb.height; y++) {
        float t = (float)y / (float)(fb.height - 1);
        for (int x = 0; x < fb.width; x++)
            fb_put(&fb, x, y, rgb_pack(v3_mix(top, bottom, t)));
    }

    uint64_t checksum = 0;
    for (int i = 0; i < fb.width * fb.height; i++)
        checksum = checksum * 31u + fb.pixels[i];

    Vec3 n = v3_norm(v3_cross(v3(1, 0, 0), v3(0, 1, 0)));
    printf("кадр %dx%d, контрольная сумма %016llx\n", fb.width, fb.height,
           (unsigned long long)checksum);
    printf("cross(X, Y) = (%.1f, %.1f, %.1f)\n", n.x, n.y, n.z);
    printf("вызовов кучи: %zu, арена занята на %zu байт\n", mem_heap_calls(), persistent.used);

    arena_destroy(&persistent);
    return 0;
}
