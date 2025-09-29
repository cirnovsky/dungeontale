/*
 * This header file describes a game map. A game map consists
 * of multiple ROOMS, between which are connected through CORRIDORS.
*/

#ifndef MAP_H
#define MAP_H


#include <ncurses.h>
#include "room.h"
#include "corridor.h"

typedef struct {
	int rooms_n, corridors_n;
	int height, width;
	Room **rooms;
	Corridor **corridors;
	Tile **tiles;
} Map;

extern Map *g_world_map;

Map *map_create(int rooms_n, int height, int width);
void map_destroy(Map *map);
void map_set(Map *map, int x, int y, int code);
Tile *map_get_tile(Map *map, int x, int y);
void map_append_corridor(Map *map, Corridor *corridor);

bool map_is_walkable(int y, int x);
int map_count_visible_tiles(void);
#endif

