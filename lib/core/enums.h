#ifndef ENUMS_H
#define ENUMS_H

#include <wchar.h>

#define MAP_HEIGHT	40
#define MAP_WIDTH	120

#define MAP_ROOMS_N	6
#define MAP_HEIGHT_ACT	40
#define MAP_WIDTH_ACT	120

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
	TILE_PORT,
	TILE_N
};

//void enums_init();

#endif
