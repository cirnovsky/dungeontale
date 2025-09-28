#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include "core/utils.h"
#include "core/enums.h"

int **numbers;

int comp(const void *a, const void *b) {
	const int *x = *(const int **) a, *y = *(const int **) b;

	return *y - *x;
}

int main() {
	setlocale(LC_ALL, "");
	int i, cnt = 0;
	int n = 114;
	int *num = malloc(n * sizeof(int));

	for (i = 0; i < n; ++i) {
		num[i] = i;
		PUSH_BACK(numbers, cnt, num + i);
	}

	qsort(numbers, n, sizeof(int *), comp);

	for (i = 0; i < cnt; ++i)
		printf(" %d", *numbers[i]);
	puts("");

	for (i = 0; i < TILE_N; ++i) {
	}
	puts("");
}
