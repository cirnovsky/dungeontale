/*
 * This header file defines the ROOM
*/

#ifndef ROOM_H
#define ROOM_H

#include "game/tile.h"

typedef struct {
	int width, height;
	int start;
	Tile *tiles;
} Room;

Room *room_create(int width, int height, int start_x, int start_y);
void room_start_coord(Room *room);
void room_destroy(Room *room);
void room_get_start(Room *room, int *x, int *y);

#endif
