#include "game/tile.h"
#include "core/enums.h"
#include <stdlib.h>

Tile *tile_create(int code) {
	Tile *tile = malloc(sizeof(Tile));

	tile_draw(tile, code);

	return tile;
}

void tile_destroy(Tile *tile) {
	free(tile);
}

void tile_draw(Tile *tile, int code) {
	tile->code = code;
}

char tile_display(Tile *tile) {
	return LEGENDS[tile->code];
}
