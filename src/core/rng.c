#include "core/rng.h"
#include "stdlib.h"
#include <sys/time.h>

unsigned int Z = 0;

void rng_seed(unsigned int seed) {
	struct timeval tv;

	gettimeofday(&tv, NULL);
	Z = seed + (tv.tv_sec ^ tv.tv_usec) | 1;
}

int rand_() {
	return (Z *= 3) >> 1;
}

int rng_range(int min, int max) {
	return rand_() % (max - min) + min;
}
