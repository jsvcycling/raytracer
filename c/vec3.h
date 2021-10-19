#ifndef MATH_H
#define MATH_H

#include <math.h>
#include <string.h>

/* The code in this file is largely inspired by `common/mathlib.h` from Quake
 * III Arena. */

typedef struct {
	double x, y, z;
} vec3_t;

static inline vec3_t vec3_new(const double x, const double y, const double z) {
	vec3_t out = { .x = x, .y = y, .z = z };
	return out;
}

static inline vec3_t vec3_add(const vec3_t *a, const vec3_t *b) {
	vec3_t out = {
		.x = a->x + b->x,
		.y = a->y + b->y,
		.z = a->z + b->z,
	};
	return out;
}

static inline void vec3_self_add(vec3_t *a, const vec3_t *b) {
	a->x += b->x;
	a->y += b->y;
	a->z += b->z;
}

static inline vec3_t vec3_sub(const vec3_t *a, const vec3_t *b) {
	vec3_t out = {
		.x = a->x - b->x,
		.y = a->y - b->y,
		.z = a->z - b->z,
	};
	return out;
}

static inline void vec3_self_sub(vec3_t *a, const vec3_t *b) {
	a->x -= b->x;
	a->y -= b->y;
	a->z -= b->z;
}

static inline vec3_t vec3_mul(const vec3_t *v, const double d) {
	vec3_t out = {
		.x = v->x * d,
		.y = v->y * d,
		.z = v->z * d,
	};
	return out;
}

static inline void vec3_self_mul(vec3_t *v, const double d) {
	v->x *= d;
	v->y *= d;
	v->z *= d;
}

static inline void vec3_copy(vec3_t *dest, const vec3_t *src) {
	memcpy(dest, src, sizeof(vec3_t));
}

static inline void vec3_neg(vec3_t *v) {
	v->x = -(v->x);
	v->y = -(v->y);
	v->z = -(v->z);
}

static inline double vec3_dot(const vec3_t *a, const vec3_t *b) {
	return a->x * b->x + a->y * b->y + a->z * b->z;
}

/* Compute the cross product between two vectors. */
static inline void vec3_cross(vec3_t *dest, const vec3_t *a, const vec3_t *b) {
	dest->x = a->y * b->z - a->z * b->y;
	dest->y = a->z * b->x - a->x * b->z;
	dest->z = a->x * b->y - a->y * b->x;
}

/* Compute the length of a vector. */
static inline double vec3_length(const vec3_t *v) {
	return sqrt(vec3_dot(v, v));
}

/* Normalize a vector to be a unit vector. */
static inline vec3_t vec3_normalize(const vec3_t *v) {
	double length = 1 / vec3_length(v);
	return vec3_mul(v, length);
}

#endif /* MATH_H */
