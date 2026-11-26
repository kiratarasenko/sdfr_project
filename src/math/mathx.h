#ifndef SDFR_MATHX_H
#define SDFR_MATHX_H

#include <math.h>

#define PI_F 3.14159265358979f

static inline float minf(float a, float b) { return a < b ? a : b; }
static inline float maxf(float a, float b) { return a > b ? a : b; }
static inline float clampf(float x, float lo, float hi) { return x < lo ? lo : (x > hi ? hi : x); }
static inline float mixf(float a, float b, float t) { return a + (b - a) * t; }
static inline float saturatef(float x) { return clampf(x, 0.0f, 1.0f); }
static inline float radiansf(float deg) { return deg * (PI_F / 180.0f); }

static inline float smoothstepf(float e0, float e1, float x)
{
    float t = saturatef((x - e0) / (e1 - e0));
    return t * t * (3.0f - 2.0f * t);
}

#endif
