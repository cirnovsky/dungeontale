#ifndef ENUMS_H
#define ENUMS_H

#define TERM_WIDTH 80
#define TERM_HEIGHT 24
#define TERM_SCALE 2
#define FONT_WIDTH 9
#define FONT_HEIGHT 16

#define MAP_HEIGHT	40
#define MAP_WIDTH	120

#define MAP_ROOMS_N	6
#define MAP_HEIGHT_ACT	40
#define MAP_WIDTH_ACT	120

extern const unsigned char LEGENDS[];

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
	TILE_PORT,
	TILE_N
};

enum Tile01 {
	TILE_OFF = 0,
	TILE_ON = 1
};

#endif
