#include "io/image.h"

#include <stdio.h>

bool image_write_ppm(const Framebuffer *fb, const char *path, Arena *scratch)
{
    FILE *f = fopen(path, "wb");
    if (!f)
        return false;

    size_t mark = arena_mark(scratch);
    size_t row_bytes = (size_t)fb->width * 3;
    uint8_t *row = arena_alloc(scratch, row_bytes, 16);

    bool ok = fprintf(f, "P6\n%d %d\n255\n", fb->width, fb->height) > 0;
    for (int y = 0; ok && y < fb->height; y++) {
        for (int x = 0; x < fb->width; x++) {
            uint32_t c = fb_get(fb, x, y);
            row[x * 3 + 0] = (uint8_t)(c >> 16);
            row[x * 3 + 1] = (uint8_t)(c >> 8);
            row[x * 3 + 2] = (uint8_t)c;
        }
        ok = fwrite(row, 1, row_bytes, f) == row_bytes;
    }

    arena_reset_to(scratch, mark);
    return (fclose(f) == 0) && ok;
}
