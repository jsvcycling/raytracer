#include "shape.h"

#include <stdlib.h>

double sphere_test_hit(sphere_t *sphere) {
	// TODO
	return 0;
}

double shape_test_hit(shape_t *shape) {
	switch (shape->type) {
		case SPHERE: return sphere_test_hit((sphere_t *)shape);
		default: abort();
	}
}
