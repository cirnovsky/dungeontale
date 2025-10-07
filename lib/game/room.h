/*
 * This header file defines the ROOM
*/

#ifndef ROOM_H
#define ROOM_H

#include "game/tile.h"
#include "game/port.h"

typedef struct {
	int height, width;
	//int start;
//详见room.c的改动
    int x;
    int y;
	int ports_n;
	Port **ports;
} Room;

Room *room_create(int height, int width, int start_x, int start_y);
void room_set_port(Room *room, Port *port);
void room_start_coord(Room *room);
void room_set_port_middle(Room *room, int lrud);
void room_get_port_coordinate(Room *room, int ind, int *x, int *y);
void room_destroy(Room *room);
void room_get_start(Room *room, int *x, int *y);
void room_get_random_coordinate(Room *room, int *x, int *y);

#endif
