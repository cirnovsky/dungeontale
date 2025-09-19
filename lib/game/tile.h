#ifndef TILE_H
#define TILE_H

#include <stdlib.h>
#include <wchar.h>

typedef struct {
	int code, state;
} Tile;

Tile *tile_create(int code);
void tile_destroy(Tile *tile);
void tile_set_state(Tile *tile, int state);
int tile_get_state(Tile *tile);
void tile_draw(Tile *tile, int code);
wchar_t tile_display(Tile *tile);

#endif
