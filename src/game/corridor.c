#include "game/corridor.h"
#include "core/utils.h"
#include <assert.h>

Corridor *corridor_create() {
	Corridor *corridor = malloc(sizeof(Corridor));

	corridor->tiles_n = 0;
	corridor->tiles = NULL;

	return corridor;
}

void corridor_append_tile(Corridor *corridor, Tile *tile) {
	assert(corridor != NULL);
	assert(tile != NULL);

	PUSH_BACK(corridor->tiles, corridor->tiles_n, tile);
}

void corridor_destroy(Corridor *corridor) {
	if (corridor == NULL)
		return;

	Tile **tiles = corridor->tiles;
	int tiles_n = corridor->tiles_n;
	int i;

	for (i = 0; i < tiles_n; ++i)
		tile_destroy(tiles[i]);

	free(tiles);
	free(corridor);
}
