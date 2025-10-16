#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <assert.h>

#define PUSH_BACK(array, count, value)							\
	do {										\
		if ((count) == 0) {							\
			assert((array) == NULL);					\
			(array) = malloc(sizeof(*array));				\
		} else if (((count) & ((count) - 1)) == 0)				\
			(array) = realloc((array), 2 * (count) * sizeof(*(array)));	\
		(array)[(count)++] = (value);						\
	} while (0);									\


int min(int a, int b);
int max(int a, int b);

#endif
