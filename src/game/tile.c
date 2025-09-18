#include "game/tile.h"
#include "core/enums.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

Tile *tile_create(int code) {
	Tile *tile = malloc(sizeof(Tile));

	tile_draw(tile, code);
	tile_set_state(tile, TILE_ON);

	return tile;
}

void tile_set_state(Tile *tile, int state) {
	assert(tile != NULL);
	tile->state = state;
}

int tile_get_state(Tile *tile) {
	assert(tile != NULL);
	return tile->state;
}

void tile_destroy(Tile *tile) {
	free(tile);
}

void tile_draw(Tile *tile, int code) {
	assert(tile != NULL);
	tile->code = code;
}

char tile_display(Tile *tile) {
	assert(tile != NULL);
	return LEGENDS[tile->code];
}
