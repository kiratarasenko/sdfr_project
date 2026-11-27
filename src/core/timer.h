#ifndef SDFR_TIMER_H
#define SDFR_TIMER_H

#include <time.h>

static inline double time_now(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

#endif
