//19/09/2025: 我严重怀疑房间变大bug出自相对坐标, 我把定位方式改成了绝对坐标
//indeed
#include "game/room.h"
#include "core/enums.h"
#include <stdlib.h>

Room *room_create(int width, int height, int x, int y) {
	Room *room = malloc(sizeof(Room));
	room->width = width;
	room->height = height;
//	room->start = x * width + y;
    room->x = x;
    room->y = y;
	return room;
}

void room_get_start(Room *room, int *x, int *y) {
//	int width = room->width, start = room->start;

//	*x = start / width;
//	*y = start % width;
    *x = room->x;
    *y = room->y;
}

void room_destroy(Room *room) {
	if (room == NULL) return;
    	//free(room->tiles);
    	free(room);
}
