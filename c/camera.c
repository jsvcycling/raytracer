#include "camera.h"

#include <stdlib.h>

vec3_t calc_lower_left_corner(
		const vec3_t *origin,
		const vec3_t *horizontal,
		const vec3_t *vertical,
		const double focal_length
);

vec3_t calc_ray_dir(
		const vec3_t *lower_left_corner,
		const double u,
		const double v,
		const vec3_t *horizontal,
		const vec3_t *vertical,
		const vec3_t *origin
);

camera_t *camera_new(void) {
	double aspect_ratio = 16.0 / 9.0;
	double viewport_height = 2.0;
	double viewport_width = aspect_ratio * viewport_height;
	double focal_length = 1.0;

	camera_t *camera = (camera_t *)malloc(sizeof(camera_t));
	camera->horizontal = vec3_new(viewport_width, 0, 0);
	camera->vertical = vec3_new(0, viewport_height, 0);

	camera->lower_left_corner = calc_lower_left_corner(
			&camera->origin,
			&camera->horizontal,
			&camera->vertical,
			focal_length
	);

	return camera;
}

void camera_free(camera_t *camera) {
	free(camera);
}

ray_t camera_get_ray(const camera_t *camera, const double u, const double v) {
	ray_t ray;
	ray.origin = camera->origin;

	ray.direction = calc_ray_dir(
			&camera->lower_left_corner,
			u,
			v,
			&camera->horizontal,
			&camera->vertical,
			&camera->origin
	);

	return ray;
}

vec3_t calc_lower_left_corner(
		const vec3_t *origin,
		const vec3_t *horizontal,
		const vec3_t *vertical,
		const double focal_length
) {
	vec3_t temp_h = vec3_mul(horizontal, 0.5);
	vec3_t temp_v = vec3_mul(vertical, 0.5);

	vec3_t focal = { .x = 0, .y = 0, .z = focal_length };

	vec3_t result = *origin;
	vec3_self_sub(&result, &temp_h);
	vec3_self_sub(&result, &temp_v);
	vec3_self_sub(&result, &focal);
	return result;
}

vec3_t calc_ray_dir(
		const vec3_t *lower_left_corner,
		const double u,
		const double v,
		const vec3_t *horizontal,
		const vec3_t *vertical,
		const vec3_t *origin
) {
	vec3_t temp_h = vec3_mul(horizontal, u);
	vec3_t temp_v = vec3_mul(vertical, v);

	vec3_t result = *lower_left_corner;
	vec3_self_add(&result, &temp_h);
	vec3_self_add(&result, &temp_v);
	vec3_self_sub(&result, origin);
	return result;
}

