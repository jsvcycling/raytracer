#include <stdio.h>

#include "color.h"
#include "shape.h"
#include "vec3.h"

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

int main() {
	/* Image */
	const double aspect_ratio = 16.0 / 9.0;
	const int image_width = 1920;
	const int image_height = (int)(image_width / aspect_ratio);

	/* World */
	shapes_t *world = shapes_new(64);

	vec3_t sphere_origin = { .x = 0, .y = 0, .z = -1 };
	shapes_add_sphere(world, sphere_origin, 0.5);

	vec3_t ground_origin = { .x = 0, .y = -100.5, .z = -1 };
	shapes_add_sphere(world, ground_origin, 100);

	/* Camera */
	double viewport_height = 2.0;
	double viewport_width = viewport_height * aspect_ratio;
	double focal_length = 1.0;

	vec3_t origin = { .x = 0, .y = 0, .z = 0 };
	vec3_t horizontal = { .x = viewport_width, .y = 0, .z = 0 };
	vec3_t vertical = { .x = 0, .y = viewport_height, .z = 0 };

	vec3_t lower_left_corner;
	calc_lower_left_corner(
			&lower_left_corner,
			&origin,
			&horizontal,
			&vertical,
			focal_length
	);

	/* Render Image */
	fprintf(stdout, "P3\n%i %i\n255\n", image_width, image_height);

	for (int j = image_height; j >= 0; --j) {
		fprintf(stderr, "Scanlines left: %i\n", j);
		for (int i = 0; i < image_width; ++i) {
			double u = i / (double)(image_width - 1);
			double v = j / (double)(image_height - 1);

			vec3_t ray_dir;
			calc_ray_dir(
					&ray_dir,
					&lower_left_corner,
					u,
					v,
					&horizontal,
					&vertical,
					&origin
			);

			ray_t ray = {
				.origin = origin,
				.direction = ray_dir,
			};

			vec3_t color;
			calc_ray_color(&color, &ray, world);
			write_color(stdout, &color);
		}
	}

	shapes_free(world);
}
