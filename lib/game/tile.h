#ifndef TILE_H
#define TILE_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int fg, bg;
	int code;
    bool is_visible;
    bool is_explored;
} Tile;

Tile *tile_create(int code, int fg, int bg);
void tile_destroy(Tile *tile);
void tile_draw(Tile *tile, int code, int fg, int bg);
unsigned char tile_display(Tile *tile);
int tilefg(Tile *tile);
int tilebg(Tile *tile);

#endif
