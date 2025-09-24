#include "game/map.h"
#include "core/enums.h"
#include <assert.h>
#include <wchar.h>
#include <stdlib.h>

Map *map_create(int rooms_n, int height, int width) {
	Map *map = malloc(sizeof(Map));
	
	map->rooms_n = rooms_n;
	map->height = height;
	map->width = width;
	map->rooms = calloc(rooms_n, sizeof(Room *));
	map->tiles = calloc(height * width, sizeof(Tile *));

	Tile **tiles = map->tiles;
	int i;

	/*for (i = 0; i < rooms_n; ++i) {
		rooms[i] = room_create(8, 8, 1, 1);
	}*/
	for (i = 0; i < height * width; ++i)
		tiles[i] = tile_create(TILE_EMPTY);

	return map;
}

void map_destroy(Map *map) {
	int i;
	int rooms_n = map->rooms_n;
	Room **rooms = map->rooms;

	for (i = 0; i < rooms_n; ++i)
		room_destroy(rooms[i]);

	int height = map->height, width = map->width;
	Tile **tiles = map->tiles;

	for (i = 0; i < height * width; ++i)
		tile_destroy(tiles[i]);

	free(map);
}

void map_set(Map *map, int x, int y, int code) {
	assert(map != NULL);

	int height = map->height, width = map->width;

	assert(0 <= x && x < height);
	assert(0 <= y && y < width);

	Tile *tile = map->tiles[x * width + y];

	tile_draw(tile, code);
}

Tile *map_get_tile(Map *map, int x, int y) {
	assert(map != NULL);

	int height = map->height, width = map->width;

	assert(0 <= x && x < height);
	assert(0 <= y && y < width);

	return map->tiles[x * width + y];
}

bool map_is_walkable(int y, int x){
    if (y < 0 || y >= g_world_map->height || x < 0 || x >= g_world_map->width){
        return false;
    }

    Tile *tile = map_get_tile(g_world_map, y, x);

    switch (tile->code){
        case TILE_WALL:
        case TILE_WALL_HOR:
        case TILE_WALL_VER:
        case TILE_WALL_COR_LU:
        case TILE_WALL_COR_RU:
        case TILE_WALL_COR_LD:
        case TILE_WALL_COR_RD:
            return false;
        default:
            return true;
    }
}
