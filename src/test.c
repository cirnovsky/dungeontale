#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include "core/utils.h"
#include "core/enums.h"

int **numbers;

int main() {
	setlocale(LC_ALL, "");
	int i, cnt = 0;
	int n = 114;
	int *num = malloc(n * sizeof(int));

	for (i = 0; i < n; ++i) {
		num[i] = i;
		PUSH_BACK(numbers, cnt, num + i);
	}

	for (i = 0; i < cnt; ++i)
		printf(" %d", *numbers[i]);
	puts("");

	for (i = 0; i < TILE_N; ++i) {
		putwchar(LEGENDS[i]);
		puts("");
	}
	puts("");
}
