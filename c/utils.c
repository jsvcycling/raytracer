#include "utils.h"

#include <stdlib.h>

double clamp(const double val, const double low, const double high) {
	if (val < low) return low;
	if (val > high) return high;
	return val;
}

double randd(void) {
	return rand() / (double)RAND_MAX;
}

double randd_range(const double low, const double high) {
	double val = randd();
	return low + val * (high - low);
}
