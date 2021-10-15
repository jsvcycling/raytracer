#include "color.h"

void write_color(FILE *f, vec3_t color) {
	int r = (int)(255.999 * color[0]);
	int g = (int)(255.999 * color[1]);
	int b = (int)(255.999 * color[2]);
	fprintf(f, "%i %i %i\n", r, g, b);
}
