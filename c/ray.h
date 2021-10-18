#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct {
	vec3_t origin;
	vec3_t direction;
} ray_t;

typedef struct {
	vec3_t point;
	vec3_t normal;
	double t;
} rayHit_t;

static inline void ray_at(vec3_t *dest, const ray_t *ray, const double t) {
	vec3_t temp_dir;
	vec3_mul(&temp_dir, &ray->direction, t);

	vec3_copy(dest, &ray->origin);
	vec3_add(dest, dest, &temp_dir);
}

static inline void ray_hit_set_face_normal(rayHit_t *hit, const ray_t *ray, const vec3_t *normal) {
	// TODO
}

#endif /* RAY_H */
