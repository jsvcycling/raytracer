#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct {
	vec3_t orig;
	vec3_t dir;
} ray_t;

#endif /* RAY_H */
