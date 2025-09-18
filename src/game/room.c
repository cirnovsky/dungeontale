
#include "game/room.h"
#include "core/enums.h"
#include <stdlib.h>

Room *room_create(int width, int height, int x, int y) {
	Room *room = malloc(sizeof(Room));
	room->width = width;
	room->height = height;
	room->tiles = calloc(width * height, sizeof(Tile));
	room->start = x * width + y;
	return room;
}

void room_get_start(Room *room, int *x, int *y) {
	int width = room->width, start = room->start;

	*x = start / width;
	*y = start % width;
}

void room_destroy(Room *room) {
	free(room);
}
