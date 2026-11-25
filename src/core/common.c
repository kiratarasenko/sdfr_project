#include "core/common.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void die(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fputs("sdfr: ошибка: ", stderr);
    vfprintf(stderr, fmt, ap);
    fputc('\n', stderr);
    va_end(ap);
    exit(1);
}
