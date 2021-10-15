#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>

#include "ray.h"
#include "vec3.h"

void write_color(FILE *f, const vec3_t *color);

void calc_ray_color(vec3_t *color, const ray_t *ray);

#endif /* COLOR_H */
