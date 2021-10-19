#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "vec3.h"

typedef struct {
	vec3_t origin;
	vec3_t lower_left_corner;
	vec3_t horizontal;
	vec3_t vertical;
} camera_t;

camera_t *camera_new(void);
void camera_free(camera_t *camera);

ray_t camera_get_ray(const camera_t *camera, const double u, const double v);

#endif /* CAMERA_H */
