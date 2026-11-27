#ifndef SDFR_IMAGE_H
#define SDFR_IMAGE_H

#include "gfx/framebuffer.h"
#include "mem/arena.h"

bool image_write_ppm(const Framebuffer *fb, const char *path, Arena *scratch);

#endif
