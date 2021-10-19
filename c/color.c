#include "color.h"

double clamp(const double val, const double low, const double high);

void write_color(FILE *f, const vec3_t *color, const int samples_per_pixel) {
	double scale = 1.0 / samples_per_pixel;
	vec3_t out = vec3_mul(color, scale);

	int r = (int)(clamp(out.x, 0, 0.999) * 256);
	int g = (int)(clamp(out.y, 0, 0.999) * 256);
	int b = (int)(clamp(out.z, 0, 0.999) * 256);

	fprintf(f, "%i %i %i\n", r, g, b);
}

vec3_t calc_ray_color(const ray_t *ray, const shapes_t *shapes) {
	rayHit_t hit;

	if (shapes_hit(shapes, ray, 0, HUGE_VAL, &hit)) {
		vec3_t ray_color = vec3_new(1, 1, 1);
		vec3_self_add(&ray_color, &hit.normal);
		return vec3_mul(&ray_color, 0.5);
	}

	vec3_t unit_dir = vec3_normalize(&ray->direction);

	double t = 0.5 * (unit_dir.y + 1.0);

	vec3_t a = vec3_new(1, 1, 1);
	vec3_self_mul(&a, (1.0 - t));

	vec3_t b = vec3_new(0.5, 0.7, 1.0);
	vec3_self_mul(&b, t);

	return vec3_add(&a, &b);
}

double clamp(const double val, const double low, const double high) {
	if (val < low) return low;
	if (val > high) return high;
	return val;
}
