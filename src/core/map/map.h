/*
 * This header file describes a game map. A game map consists
 * of multiple ROOMS, between which are connected through CORRIDORS.
*/

#ifndef MAP_H
#define MAP_H

#include "room.h"

typedef struct {
	int rooms_n;
	Room *rooms;
} Map;

Map *map_create(int n);
void map_destroy();

