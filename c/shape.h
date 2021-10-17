#ifndef SHAPE_H
#define SHAPE_H

typedef enum {
	SPHERE,
} shapeType_t;

typedef struct {
	shapeType_t type;
} shape_t;

typedef struct {
	shape_t super;

	/* TODO */
} sphere_t;

double shape_test_hit(shape_t *shape);

#endif /* SHAPE_H */
