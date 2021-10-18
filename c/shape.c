#include "shape.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHAPE_UNKNOWN    0
#define SHAPE_SPHERE     1 

typedef struct {
	vec3_t origin;
	double radius;
} sphere_t;

int shape_hit_sphere(const sphere_t *sphere, const ray_t *ray, const double t_min, const double t_max, rayHit_t *hit);

shapes_t *shapes_new(const unsigned int capacity) {
	shapes_t *shapes = (shapes_t *)malloc(sizeof(shapes_t));
	shapes->shapes = (void **)calloc(capacity, sizeof(void *));
	shapes->types = (int *)calloc(capacity, sizeof(int));
	shapes->capacity = capacity;
	shapes->count = 0;
	return shapes;
}

void shapes_free(shapes_t *shapes) {
	for (int i = 0; i < shapes->count; i++) {
		free(shapes->shapes[i]);
	}

	free(shapes->shapes);
	free(shapes->types);
	free(shapes);
}

int shapes_hit(const shapes_t *shapes, const ray_t *ray, const double t_min, const double t_max, rayHit_t *hit) {
	int hit_anything = 0;
	double closest = t_max;

	for (unsigned int i = 0; i < shapes->count; i++) {
		int type = shapes->types[i];
		void *shape = shapes->shapes[i];
		rayHit_t temp_hit;

		if (type == SHAPE_SPHERE) {
			if (shape_hit_sphere((sphere_t *)shape, ray, t_min, closest, &temp_hit)) {
				hit_anything = 1;
				closest = temp_hit.t;
				memcpy(hit, &temp_hit, sizeof(rayHit_t));
			}
		} else {
			fprintf(stderr, "Encountered unknown shape type code %i. Aborting.\n", type);
			abort();
		}
	}

	return hit_anything;
}

void shapes_add_sphere(shapes_t *shapes, const vec3_t origin, const double radius) {
	if (shapes->count == shapes->capacity) abort();

	/* Create the sphere. */
	sphere_t *sphere = (sphere_t *)malloc(sizeof(sphere_t));
	vec3_copy(&sphere->origin, &origin);
	sphere->radius = radius;

	/* Add the sphere to to the list of shapes. */
	shapes->shapes[shapes->count] = (void *)sphere;
	shapes->types[shapes->count] = SHAPE_SPHERE;
	shapes->count += 1;
}

int shape_hit_sphere(const sphere_t *sphere, const ray_t *ray, const double t_min, const double t_max, rayHit_t *hit) {
	vec3_t oc;
	vec3_copy(&oc, &ray->origin);
	vec3_sub(&oc, &oc, &sphere->origin);

	double a = vec3_dot(&ray->direction, &ray->direction);
	double half_b = vec3_dot(&oc, &ray->direction);
	double c = vec3_dot(&oc, &oc) - sphere->radius * sphere->radius;

	double descriminant = half_b * half_b - a * c;
	if (descriminant < 0.0) return 0;
	double sqrtd = sqrt(descriminant);

	double root = (-half_b - sqrtd) / a;
	if (root < t_min || root > t_max) {
		root = (-half_b - sqrtd) / a;
		if (root < t_min || root > t_max) return 0;
	}

	hit->t = root;
	ray_at(&hit->point, ray, root);

	vec3_t outward_normal;
	vec3_copy(&outward_normal, &hit->point);
	vec3_sub(&outward_normal, &outward_normal, &sphere->origin);
	vec3_mul(&outward_normal, &outward_normal, 1 / sphere->radius);
	ray_hit_set_face_normal(hit, ray, &outward_normal);

	return 1;
}

