/*
 * This header file defines the ROOM
*/

#ifndef ROOM_H
#define ROOM_H

#include "tile.h"

typedef struct {
	int width, height;
	Tile *tiles;
} Room;

Room *room_create(int width, int height);
void room_destroy(Room *room);

#endif
