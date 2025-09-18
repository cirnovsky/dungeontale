
#include "room.h"
#include <stdlib.h>

Room *room_create(int width, int height) {
	Room *room = malloc(sizeof(Room));
	room->width = width;
	room->height = height;
	room->tiles = calloc(width * height, sizeof(Tile));
	return room;
}

void room_destroy(Room *room) {
	room->(room
