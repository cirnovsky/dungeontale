/*
 * This header file describes a game map. A game map consists
 * of multiple ROOMS, between which are connected through CORRIDORS.
*/

#ifndef MAP_H
#define MAP_H


#include <ncurses.h>
#include "room.h"

typedef struct {
	int rooms_n;
	int height, width;
	Room **rooms;
	Tile **tiles;
} Map;

Map *map_create(int rooms_n, int height, int width);
void map_destroy(Map *map);
void map_set(Map *map, int x, int y, int code);
void map_init();
Tile *map_get_tile(Map *map, int x, int y);

void map_draw(WINDOW *win);
int map_is_walkable(int y, int x);

#endif

