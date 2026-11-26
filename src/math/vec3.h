#ifndef SDFR_VEC3_H
#define SDFR_VEC3_H

#include "math/mathx.h"

typedef struct Vec3 {
    float x, y, z;
} Vec3;

static inline Vec3  v3(float x, float y, float z)   { return (Vec3){ x, y, z }; }
static inline Vec3  v3s(float s)                     { return (Vec3){ s, s, s }; }
static inline Vec3  v3_add(Vec3 a, Vec3 b)           { return v3(a.x + b.x, a.y + b.y, a.z + b.z); }
static inline Vec3  v3_sub(Vec3 a, Vec3 b)           { return v3(a.x - b.x, a.y - b.y, a.z - b.z); }
static inline Vec3  v3_mul(Vec3 a, Vec3 b)           { return v3(a.x * b.x, a.y * b.y, a.z * b.z); }
static inline Vec3  v3_scale(Vec3 a, float s)        { return v3(a.x * s, a.y * s, a.z * s); }
static inline Vec3  v3_madd(Vec3 a, Vec3 b, float s) { return v3(a.x + b.x * s, a.y + b.y * s, a.z + b.z * s); }
static inline float v3_dot(Vec3 a, Vec3 b)           { return a.x * b.x + a.y * b.y + a.z * b.z; }
static inline float v3_len(Vec3 a)                   { return sqrtf(v3_dot(a, a)); }
static inline Vec3  v3_abs(Vec3 a)                   { return v3(fabsf(a.x), fabsf(a.y), fabsf(a.z)); }
static inline Vec3  v3_maxs(Vec3 a, float s)         { return v3(maxf(a.x, s), maxf(a.y, s), maxf(a.z, s)); }
static inline Vec3  v3_mix(Vec3 a, Vec3 b, float t)  { return v3(mixf(a.x, b.x, t), mixf(a.y, b.y, t), mixf(a.z, b.z, t)); }

static inline Vec3 v3_cross(Vec3 a, Vec3 b)
{
    return v3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

static inline Vec3 v3_norm(Vec3 a)
{
    float l = v3_len(a);
    return l > 0.0f ? v3_scale(a, 1.0f / l) : a;
}

#endif
