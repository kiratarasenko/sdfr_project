#include "gfx/framebuffer.h"

void fb_init(Framebuffer *fb, Arena *arena, int width, int height)
{
    if (width <= 0 || height <= 0)
        die("некорректный размер кадра %dx%d", width, height);
    fb->width  = width;
    fb->height = height;
    fb->pixels = arena_alloc(arena, sizeof(uint32_t) * (size_t)width * (size_t)height, 64);
    fb_clear(fb, 0xFF000000u);
}

void fb_clear(Framebuffer *fb, uint32_t color)
{
    size_t n = (size_t)fb->width * (size_t)fb->height;
    for (size_t i = 0; i < n; i++)
        fb->pixels[i] = color;
}
