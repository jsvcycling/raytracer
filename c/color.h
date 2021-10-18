#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>

#include "ray.h"
#include "shape.h"
#include "vec3.h"

void write_color(FILE *f, const vec3_t *color);

void calc_ray_color(vec3_t *color, const ray_t *ray, const shapes_t *shapes);

#endif /* COLOR_H */
