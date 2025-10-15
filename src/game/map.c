#include "game/map.h"
#include "core/enums.h"
#include "core/utils.h"
#include "core/ui.h"
#include <assert.h>
#include <wchar.h>
#include <stdlib.h>

Map *map_create(int rooms_n, int height, int width) {
	Map *map = malloc(sizeof(Map));
	
	map->rooms_n = rooms_n;
	map->corridors_n = 0;
	map->height = height;
	map->width = width;
	map->rooms = calloc(rooms_n, sizeof(Room *));
	map->corridors = NULL;
	map->tiles = calloc(height * width, sizeof(Tile *));

	Tile **tiles = map->tiles;
	int i;

	for (i = 0; i < height * width; ++i)
		tiles[i] = tile_create(TILE_EMPTY, COLOR_BLACK, COLOR_BLACK);

	return map;
}

void map_append_corridor(Map *map, Corridor *corridor) {
	assert(map != NULL);
	assert(corridor != NULL);

	PUSH_BACK(map->corridors, map->corridors_n, corridor);
}

void map_destroy(Map *map) {
	int i;
	int rooms_n = map->rooms_n;
	Room **rooms = map->rooms;

	for (i = 0; i < rooms_n; ++i)
		room_destroy(rooms[i]);
	free(map->rooms);

	int height = map->height, width = map->width;
	Tile **tiles = map->tiles;

	for (i = 0; i < height * width; ++i)
		tile_destroy(tiles[i]);
	free(map->tiles);

	int corridors_n = map->corridors_n;
	Corridor **corridors = map->corridors;

	for (i = 0; i < corridors_n; ++i)
		corridor_destroy(corridors[i]);
	free(map->corridors);

	free(map);
}

void map_set(Map *map, int x, int y, int code, int fg, int bg) {
	assert(map != NULL);

	int height = map->height, width = map->width;

	assert(0 <= x && x < height);
	assert(0 <= y && y < width);

	Tile *tile = map->tiles[x * width + y];

	tile_draw(tile, code, fg, bg);
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
	case TILE_EMPTY:
            return false;
        default:
            return true;
    }
}


int map_count_visible_tiles(void) {
    if (g_world_map == NULL) {
        return -1;
    }
    
    int count = 0;
    int total_tiles = g_world_map->height * g_world_map->width;
    
    for (int i = 0; i < total_tiles; i++) {
        if (g_world_map->tiles[i]->is_visible) {
            count++;
        }
    }
    return count;
}
