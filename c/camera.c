#include "camera.h"

#include <stdlib.h>

void calc_lower_left_corner(
		vec3_t *dest,
		const vec3_t *origin,
		const vec3_t *horizontal,
		const vec3_t *vertical,
		const double focal_length
);

void calc_ray_dir(
		vec3_t *dest,
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

	camera_t *camera = (camera_t *)calloc(1, sizeof(camera_t));
	camera->horizontal.x = viewport_width;
	camera->vertical.y = viewport_height;

	calc_lower_left_corner(
			&camera->lower_left_corner,
			&camera->origin,
			&camera->horizontal,
			&camera->vertical,
			focal_length
	);

	return camera;
}

ray_t camera_get_ray(const camera_t *camera, const double u, const double v) {
	ray_t ray;
	vec3_copy(&ray.origin, &camera->origin);
	calc_ray_dir(
			&ray.direction,
			&camera->lower_left_corner,
			u,
			v,
			&camera->horizontal,
			&camera->vertical,
			&camera->origin
	);

	return ray;
}

void calc_lower_left_corner(
		vec3_t *dest,
		const vec3_t *origin,
		const vec3_t *horizontal,
		const vec3_t *vertical,
		const double focal_length
) {
	vec3_t temp_h, temp_v;
	vec3_mul(&temp_h, horizontal, 0.5);
	vec3_mul(&temp_v, vertical, 0.5);

	vec3_t focal = { .x = 0, .y = 0, .z = focal_length };

	vec3_copy(dest, origin);
	vec3_sub(dest, dest, &temp_h);
	vec3_sub(dest, dest, &temp_v);
	vec3_sub(dest, dest, &focal);
}

void calc_ray_dir(
		vec3_t *dest,
		const vec3_t *lower_left_corner,
		const double u,
		const double v,
		const vec3_t *horizontal,
		const vec3_t *vertical,
		const vec3_t *origin
) {
	vec3_t temp_h, temp_v;
	vec3_mul(&temp_h, horizontal, u);
	vec3_mul(&temp_v, vertical, v);

	vec3_copy(dest, lower_left_corner);
	vec3_add(dest, dest, &temp_h);
	vec3_add(dest, dest, &temp_v);
	vec3_sub(dest, dest, origin);
}

