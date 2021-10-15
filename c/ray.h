#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct {
	vec3_t orig;
	vec3_t dir;
} ray_t;

static inline void ray_at(vec3_t *dest, const ray_t *ray, const double t) {
	vec3_t temp_dir;
	vec3_mul(&temp_dir, &ray->dir, t);

	vec3_copy(dest, &ray->orig);
	vec3_add(dest, dest, &temp_dir);
}

#endif /* RAY_H */
