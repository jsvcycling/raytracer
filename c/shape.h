#ifndef SHAPE_H
#define SHAPE_H

#include "ray.h"
#include "vec3.h"

typedef struct {
	void **shapes;
	int *types;
	unsigned int capacity;
	unsigned int count;
} shapes_t;

/* Create a new shape list. */
shapes_t *shapes_new(const unsigned int capacity);

/* Deallocate a shape list (and all shapes in it). */
void shapes_free(shapes_t *shapes);

/* Test if any shapes are hit by a ray, and if so, where the hit occurred. */
int shapes_hit(const shapes_t *shapes, const ray_t *ray, const double t_min, const double t_max, rayHit_t *hit);

/* Add a sphere to the shape list. */
void shapes_add_sphere(shapes_t *shapes, const vec3_t origin, const double radius);

#endif /* SHAPE_H */
