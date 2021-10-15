#ifndef MATH_H
#define MATH_H

#include <math.h>
#include <string.h>

/* The code in this file is largely inspired by `common/mathlib.h` from Quake
 * III Arena. */

typedef struct {
	double x, y, z;
} vec3_t;

/* Perform element-wise addition between two vectors. */
static inline void vec3_add(vec3_t *dest, const vec3_t *a, const vec3_t *b) {
	dest->x = a->x + b->x;
	dest->y = a->y + b->y;
	dest->z = a->z + b->z;
}

/* Perform element-wise subtraction between two vectors. */
static inline void vec3_sub(vec3_t *dest, const vec3_t *a, const vec3_t *b) {
	dest->x = a->x - b->x;
	dest->y = a->y - b->y;
	dest->z = a->z - b->z;
}

/* Scale a vector by multiplying it by a constant. */
static inline void vec3_mul(vec3_t *dest, const vec3_t *v, const double d) {
	dest->x = v->x * d;
	dest->y = v->y * d;
	dest->z = v->z * d;
}

/* Copy the value of one vector to another. */
static inline void vec3_copy(vec3_t *dest, const vec3_t *src) {
	memcpy(dest, src, sizeof(double) * 3);
}

/* Negate a vector in-place. */
static inline void vec3_neg(vec3_t *v) {
	v->x = -(v->x);
	v->y = -(v->y);
	v->z = -(v->z);
}

/* Compute the dot product between two vectors. */
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
static inline void vec3_normalize(vec3_t *dest, const vec3_t *v) {
	double length = 1 / vec3_length(v);
	vec3_mul(dest, v, length);
}

#endif /* MATH_H */
