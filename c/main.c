#include <stdio.h>

#include "camera.h"
#include "color.h"
#include "shape.h"
#include "utils.h"
#include "vec3.h"

int main() {
	/* Image */
	const double aspect_ratio = 16.0 / 9.0;
	const int image_width = 1280;
	const int image_height = (int)(image_width / aspect_ratio);
	const int samples_per_pixel = 25;

	/* World */
	shapes_t *world = shapes_new(64);
	shapes_add_sphere(world, vec3_new(0, 0, -1), 0.5);
	shapes_add_sphere(world, vec3_new(0, -100.5, -1), 100);

	/* Camera */
	camera_t *camera = camera_new();

	/* Render Image */
	fprintf(stdout, "P3\n%i %i\n255\n", image_width, image_height);

	for (int j = image_height; j >= 0; --j) {
		fprintf(stderr, "Scanlines left: %i\n", j);
		for (int i = 0; i < image_width; ++i) {
			vec3_t pixel_color = vec3_new(0, 0, 0);

			for (int s = 0; s < samples_per_pixel; s++) {
				double u = (i + randd()) / (double)(image_width - 1);
				double v = (j + randd()) / (double)(image_height - 1);

				ray_t ray = camera_get_ray(camera, u, v);
				vec3_t color = calc_ray_color(&ray, world);
				vec3_self_add(&pixel_color, &color);
			}

			write_color(stdout, &pixel_color, samples_per_pixel);
		}
	}

	camera_free(camera);
	shapes_free(world);
}
