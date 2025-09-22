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
	free(map->rooms);
	free(map);
}

static wchar_t map_layout[MAP_HEIGHT][MAP_WIDTH + 1];

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


int map_is_walkable(int y, int x){
    if (y < 0 || y >= MAP_HEIGHT || x < 0 || x >= MAP_WIDTH){
        return 0;
    }
    return map_layout[y][x] != '#';
}
