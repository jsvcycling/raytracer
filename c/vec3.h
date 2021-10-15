#ifndef MATH_H
#define MATH_H

#include <math.h>

/* The code in this file is largely inspired by `common/mathlib.h` from Quake
 * III Arena. */

typedef double vec3_t[3];

/* Copy the value of one vector to another. */
#define vec3_copy(a, b) { \
	b[0] = a[0]; \
	b[1] = a[1]; \
	b[2] = a[2]; \
}

/* Perform element-wise addition between two vectors. */
#define vec3_add(a, b, c) { \
	c[0] = a[0] + b[0]; \
	c[1] = a[1] + b[1]; \
	c[2] = a[2] + b[2]; \
}

/* Perform element-wise subtraction between two vectors. */
#define vec3_sub(a, b, c) { \
	c[0] = a[0] - b[0]; \
	c[1] = a[1] - b[1]; \
	c[2] = a[2] - b[2]; \
}

/* Scale a vector by multiplying it by a constant. */
#define vec3_mul(a, b, c) { \
	c[0] = a[0] * b; \
	c[1] = a[1] * b; \
	c[2] = a[2] * b; \
}

/* Scale a vector by dividing it by a constant. */
#define vec3_div(a, b, c) { \
	c[0] = a[0] / b; \
	c[1] = a[0] / b; \
	c[2] = a[0] / b; \
}

/* Negate a vector in-place. */
#define vec3_neg(a) {a[0] = -a[0]; a[1] = -a[1]; a[2] = -a[2]; }

/* Compute the dot product between two vectors. */
#define vec3_dot(a, b) (a[0] * b[0] + a[1] * b[1] + a[2] * b[2])

/* Compute the cross product between two vectors. */
#define vec3_cross(a, b, c) { \
	c[0] = a[1] * b[2] - a[2] * b[1]; \
	c[1] = a[2] * b[0] - a[0] * b[2]; \
	c[2] = a[0] * b[1] - a[1] * b[0]; \
}

/* Compute the squared length of a vector. */
#define vec3_sqrlen(a) vec3_dot(a, a)

/* Compute the length of a vector. */
#define vec3_len(a) sqrt(vec3_sqrlen(a))

/* Compute the unit vector of a vector. */
#define vec3_unit(a, b) vec3_div(a, vec3_len(a), b)

#endif /* MATH_H */
