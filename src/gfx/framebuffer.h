#ifndef SDFR_FRAMEBUFFER_H
#define SDFR_FRAMEBUFFER_H

#include "core/common.h"
#include "mem/arena.h"
#include "math/vec3.h"

typedef struct Framebuffer {
    int       width;
    int       height;
    uint32_t *pixels;
} Framebuffer;

void fb_init(Framebuffer *fb, Arena *arena, int width, int height);
void fb_clear(Framebuffer *fb, uint32_t color);

static inline uint32_t rgb_pack(Vec3 c)
{
    uint32_t r = (uint32_t)(saturatef(c.x) * 255.0f + 0.5f);
    uint32_t g = (uint32_t)(saturatef(c.y) * 255.0f + 0.5f);
    uint32_t b = (uint32_t)(saturatef(c.z) * 255.0f + 0.5f);
    return 0xFF000000u | (r << 16) | (g << 8) | b;
}

static inline void fb_put(Framebuffer *fb, int x, int y, uint32_t c)
{
    fb->pixels[(size_t)y * (size_t)fb->width + (size_t)x] = c;
}

static inline uint32_t fb_get(const Framebuffer *fb, int x, int y)
{
    return fb->pixels[(size_t)y * (size_t)fb->width + (size_t)x];
}

#endif
