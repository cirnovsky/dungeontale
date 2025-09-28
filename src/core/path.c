#include "core/path.h"
#include "core/utils.h"
#include <assert.h>

Tile **path_find(Map *map, int x1, int y1, int x2, int y2, int hv, int *cnt) {
	assert(map != NULL);

	int height = map->height, width = map->width;

	assert(0 <= x1 && x1 < height);
	assert(0 <= x2 && x2 < height);
	assert(0 <= y1 && y1 < width);
	assert(0 <= y2 && y2 < width);

	Tile **tiles = NULL;
	int i, j;
	
	assert(*cnt == 0);

	if (hv) {
		// vertical
		for (i = x1; i <= (x1 + x2) / 2; ++i) {
			Tile *tile = map_get_tile(map, i, y1);

			PUSH_BACK(tiles, *cnt, tile);
		}
		for (i = x1; i >= (x1 + x2) / 2; --i) {
			Tile *tile = map_get_tile(map, i, y1);

			PUSH_BACK(tiles, *cnt, tile);
		}
		for (i = x2; i <= (x1 + x2) / 2; ++i) {
			Tile *tile = map_get_tile(map, i, y2);

			PUSH_BACK(tiles, *cnt, tile);
		}
		for (i = x2; i >= (x1 + x2) / 2; --i) {
			Tile *tile = map_get_tile(map, i, y2);

			PUSH_BACK(tiles, *cnt, tile);
		}

		for (j = min(y1, y2) + 1; j < max(y1, y2); ++j) {
			Tile *tile = map_get_tile(map, (x1 + x2) / 2, j);

			PUSH_BACK(tiles, *cnt, tile);
		}
	} else {
		for (j = y1; j <= (y1 + y2) / 2; ++j) {
			Tile *tile = map_get_tile(map, x1, j);

			PUSH_BACK(tiles, *cnt, tile);
		}
		for (j = y1; j >= (y1 + y2) / 2; --j) {
			Tile *tile = map_get_tile(map, x1, j);

			PUSH_BACK(tiles, *cnt, tile);
		}
		for (j = y2; j <= (y1 + y2) / 2; ++j) {
			Tile *tile = map_get_tile(map, x2, j);

			PUSH_BACK(tiles, *cnt, tile);
		}
		for (j = y2; j >= (y1 + y2) / 2; --j) {
			Tile *tile = map_get_tile(map, x2, j);

			PUSH_BACK(tiles, *cnt, tile);
		}

		for (i = min(x1, x2) + 1; i < max(x1, x2); ++i) {
			Tile *tile = map_get_tile(map, i, (y1 + y2) / 2);

			PUSH_BACK(tiles, *cnt, tile);
		}
	}

	return tiles;
}
