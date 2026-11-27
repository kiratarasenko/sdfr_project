#include <stdio.h>

#include "core/common.h"
#include "core/timer.h"
#include "mem/arena.h"
#include "mem/mem_stats.h"
#include "math/vec3.h"
#include "gfx/framebuffer.h"
#include "io/image.h"

int main(int argc, char **argv)
{
    const char *out = argc > 1 ? argv[1] : "out.ppm";
    printf("sdfr %s — программный SDF-рендерер здания (CPU, C + NASM)\n", SDFR_VERSION);

    Arena persistent, scratch;
    if (!arena_init(&persistent, MIB(64), "persistent") || !arena_init(&scratch, MIB(16), "scratch"))
        die("не удалось выделить арены");

    Framebuffer fb;
    fb_init(&fb, &persistent, 640, 360);

    double t0 = time_now();
    Vec3 sky_top = v3(0.30f, 0.50f, 0.85f);
    Vec3 sky_low = v3(0.85f, 0.88f, 0.92f);
    Vec3 ground  = v3(0.35f, 0.40f, 0.30f);
    for (int y = 0; y < fb.height; y++) {
        float v = (float)y / (float)(fb.height - 1);
        for (int x = 0; x < fb.width; x++) {
            float u = (float)x / (float)(fb.width - 1);
            Vec3 c = v < 0.6f ? v3_mix(sky_top, sky_low, v / 0.6f)
                              : v3_mix(ground, v3_scale(ground, 0.5f), (v - 0.6f) / 0.4f);
            float checker = (((int)(u * 16) + (int)(v * 9)) & 1) ? 1.0f : 0.92f;
            fb_put(&fb, x, y, rgb_pack(v3_scale(c, checker)));
        }
    }
    double t1 = time_now();

    if (!image_write_ppm(&fb, out, &scratch))
        die("не удалось записать %s", out);

    printf("тестовый кадр %dx%d заполнен за %.2f мс и записан в %s\n",
           fb.width, fb.height, (t1 - t0) * 1e3, out);
    printf("вызовов кучи: %zu\n", mem_heap_calls());

    arena_destroy(&scratch);
    arena_destroy(&persistent);
    return 0;
}
