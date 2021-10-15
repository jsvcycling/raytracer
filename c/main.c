#include <stdio.h>

#include "color.h"
#include "vec3.h"

const int IMAGE_WIDTH = 256;
const int IMAGE_HEIGHT = 256;

int main() {
	fprintf(stdout, "P3\n%i %i\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);

	for (int j = IMAGE_HEIGHT; j >= 0; j--) {
		for (int i = 0; i < IMAGE_WIDTH; ++i) {
			vec3_t color;
			color[0] = (double)i / (IMAGE_WIDTH - 1);
			color[1] = (double)j / (IMAGE_HEIGHT - 1);
			color[2] = 0.25;
			write_color(stdout, color);
		}
	}
}
