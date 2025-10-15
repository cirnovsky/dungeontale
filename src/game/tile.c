#include "game/tile.h"
#include "core/enums.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

Tile *tile_create(int code, int fg, int bg) {
	Tile *tile = malloc(sizeof(Tile));
    tile->is_visible = false;
    tile->is_explored = false;
	tile_draw(tile, code, fg, bg);

	return tile;
}

void tile_destroy(Tile *tile) {
	if (tile == NULL)
		return;

	free(tile);
}

void tile_draw(Tile *tile, int code, int fg, int bg) {
	assert(tile != NULL);
	tile->code = code;
	tile->fg = fg;
	tile->bg = bg;
}


unsigned char tile_display(Tile *tile) {
	assert(tile != NULL);
	return LEGENDS[tile->code];
}

int tilefg(Tile *tile) {
	assert(tile != NULL);
	return tile->fg;
}
int tilebg(Tile *tile) {
	assert(tile != NULL);
	return tile->bg;
}
