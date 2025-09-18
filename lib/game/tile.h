#ifndef TILE_H
#define TILE_H

#include <stdlib.h>

typedef struct {
	int code;
} Tile;

Tile *tile_create(int code);
void tile_destroy(Tile *tile);
void tile_draw(Tile *tile, int code);
char tile_display(Tile *tile);

#endif
