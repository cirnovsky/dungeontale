#ifndef ENUMS_H
#define ENUMS_H

#include <wchar.h>

#define MAP_HEIGHT 20
#define MAP_WIDTH 60

extern const wchar_t *LEGENDS;

enum Tiles {
	TILE_EMPTY = 0,
	TILE_WALL,
	TILE_ROOM,
	TILE_CORRIDOR,
	TILE_WALL_HOR,
	TILE_WALL_VER,
	TILE_WALL_COR_LU,
	TILE_WALL_COR_RU,
	TILE_WALL_COR_LD,
	TILE_WALL_COR_RD,
	TILE_ON,
	TILE_OFF,
	TILE_N
};

//void enums_init();

#endif
