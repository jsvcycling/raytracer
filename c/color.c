#include "color.h"

void write_color(FILE *f, const vec3_t *color, const int samples_per_pixel) {
	double scale = 1.0 / samples_per_pixel;

	/* Gamma-correction */
	double r = sqrt(scale * color->x);
	double g = sqrt(scale * color->y);
	double b = sqrt(scale * color->z);

	r = (clamp(r, 0, 0.999) * 256);
	g = (clamp(g, 0, 0.999) * 256);
	b = (clamp(b, 0, 0.999) * 256);

	fprintf(f, "%i %i %i\n", (int)r, (int)g, (int)b);
}

vec3_t calc_ray_color(const ray_t *ray, const shapes_t *shapes, const int level) {
	rayHit_t hit;

	if (level <= 0) return vec3_new(0, 0, 0);

	if (shapes_hit(shapes, ray, 0.001, HUGE_VAL, &hit)) {
		vec3_t target = hit.point;
		vec3_self_add(&target, &hit.normal);
		vec3_t rand_vec = vec3_rand_unit_vector();
		vec3_self_add(&target, &rand_vec);

		ray_t subRay = {
			.origin = hit.point,
			.direction = vec3_sub(&target, &hit.point),
		};

		vec3_t subRayColor = calc_ray_color(&subRay, shapes, level - 1);
		return vec3_mul(&subRayColor, 0.5);
	}

	vec3_t unit_dir = vec3_normalize(&ray->direction);

	double t = 0.5 * (unit_dir.y + 1.0);

	vec3_t a = vec3_new(1, 1, 1);
	vec3_self_mul(&a, (1.0 - t));

	vec3_t b = vec3_new(0.5, 0.7, 1.0);
	vec3_self_mul(&b, t);

	return vec3_add(&a, &b);
}
