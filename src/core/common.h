#ifndef SDFR_COMMON_H
#define SDFR_COMMON_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define SDFR_VERSION "0.2.0"

#define ARRAY_LEN(a)   (sizeof(a) / sizeof((a)[0]))
#define KIB(x)         ((size_t)(x) << 10)
#define MIB(x)         ((size_t)(x) << 20)
#define ALIGN_UP(x, a) (((x) + ((a) - 1)) & ~((size_t)(a) - 1))
#define ALIGN32        _Alignas(32)

#define UNUSED(x) ((void)(x))

_Noreturn void die(const char *fmt, ...) __attribute__((format(printf, 1, 2)));

#endif
