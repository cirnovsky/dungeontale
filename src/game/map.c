#include "game/map.h"
#include "core/ui.h"
#include "core/enums.h"
#include <assert.h>
#include <stdlib.h>

Map *map_create(int rooms_n, int height, int width) {
	Map *map = malloc(sizeof(Map));
	
	map->rooms_n = rooms_n;
	map->height = height;
	map->width = width;
	map->rooms = calloc(rooms_n, sizeof(Room *));
	map->tiles = calloc(height * width, sizeof(Tile *));

	Room **rooms = map->rooms;
	Tile **tiles = map->tiles;
	int i;

	for (i = 0; i < rooms_n; ++i)
		rooms[i] = room_create(5, 5, 0, 0);
	for (i = 0; i < height * width; ++i)
		tiles[i] = tile_create(TILE_EMPTY);

	return map;
}

void map_destroy(Map *map) {
	free(map->rooms);
	free(map);
}

#define MAP_HEIGHT 20
#define MAP_WIDTH 60

static char map_layout[MAP_HEIGHT][MAP_WIDTH];

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

void room_draw(Room *room, Map *map) {
	assert(room != NULL);
	assert(map != NULL);

	int height = room->height, width = room->width;
	int start_x, start_y;
	int i, j;

	room_get_start(room, &start_x, &start_y);
	for (i = 0; i < height; ++i) {
		map_set(map, i, start_y, TILE_WALL);
		map_set(map, i, start_y + width - 1, TILE_WALL);
	}
	for (j = 0; j < width; ++j) {
		map_set(map, start_x, j, TILE_WALL);
		map_set(map, start_x + height - 1, start_y, TILE_WALL);
	}
}

/*
 * Write part of @*map to @map_layout
 * starting from (@x, @y)
*/
void map_write(Map *map, int x, int y) {
	assert(map != NULL);

	int i, j;

	for (i = 0; i < MAP_HEIGHT; ++i) {
		for (j = 0; j < MAP_WIDTH; ++j) {
			Tile *tile = map_get_tile(map, i + x, j + y);

			map_layout[i][j] = tile_display(tile);
		}
	}
}

void map_init() {
	Map *map = map_create(1, MAP_HEIGHT, MAP_WIDTH);
	int i;

	for (i = 0; i < MAP_HEIGHT; ++i) {
		map_set(map, i, 0, TILE_WALL);
		map_set(map, i, MAP_WIDTH - 1, TILE_WALL);
	}
	for (i = 0; i < MAP_WIDTH; ++i) {
		map_set(map, 0, i, TILE_WALL);
		map_set(map, MAP_HEIGHT - 1, i, TILE_WALL);
	}

	return map_write(map, 0, 0);

	Room **room = map->rooms;
	int rooms_n = map->rooms_n;

	for (i = 0; i < rooms_n; ++i)
		room_draw(room[i], map);

	map_write(map, 0, 0);
}

void map_draw(){
    for (int y = 0; y < MAP_HEIGHT; ++y){
        mvwprintw(win_main, y+1, 1, "%s", map_layout[y]);    
    }
}

int map_is_walkable(int y, int x){
    if (y < 0 || y >= MAP_HEIGHT || x < 0 || x >= MAP_WIDTH){
        return 0;
    }
    return map_layout[y][x] != '#';
}
