//19/09/2025: 我严重怀疑房间变大bug出自相对坐标, 我把定位方式改成了绝对坐标
//indeed
#include "core/enums.h"
#include "core/utils.h"
#include "game/room.h"
#include <stdlib.h>

Room *room_create(int height, int width, int x, int y) {
	Room *room = malloc(sizeof(Room));

	room->height = height;
	room->width = width;
//	room->start = x * width + y;
    room->x = x;
    room->y = y;
	room->ports_n = 0;
	room->ports = NULL;

	return room;
}

void room_set_port(Room *room, Port *port) {
	assert(room != NULL);
	assert(port != NULL);

	int lrud = port->LRUD, offset = port->offset;
	int height = room->height, width = room->width;

	if (lrud < 2)
		assert(offset < width);
	else
		assert(offset < height);
	
	PUSH_BACK(room->ports, room->ports_n, port);
}

void room_set_port_middle(Room *room, int lrud) {
	assert(room != NULL);

	int height = room->height, width = room->width;
	int offset;

	if (lrud < 2)
		offset = height / 2;
	else
		offset = width / 2;

	PUSH_BACK(room->ports, room->ports_n, port_create(lrud, offset));
}

void room_get_port_coordinate(Room *room, int port, int *x, int *y) {
	assert(room != NULL);

	int height = room->height, width = room->width;
	int startx, starty;

	room_get_start(room, &startx, &starty);

	Port **ports = room->ports;
	int ports_n = room->ports_n;

	assert(0 <= port && port < ports_n);

	int lrud = ports[port]->LRUD, offset = ports[port]->offset;

	*x = startx + (lrud < 2) * offset + (lrud == 3) * (height - 1);
	*y = starty + (lrud >= 2) * offset + (lrud == 1) * (width - 1);
}

void room_get_random_coordinate(Room *room, int *x, int *y) {
	assert(room != NULL);

	int height = room->height, widht = room->width;
	int sx, sy;

	room_get_start(room, &sx, &sy);

	*x = sx + rng_range(1, height - 1);
	*y = sy + rng_range(1, width - 1);
}

void room_get_start(Room *room, int *x, int *y) {
//	int width = room->width, start = room->start;

//	*x = start / width;
//	*y = start % width;
	assert(room != NULL);
    *x = room->x;
    *y = room->y;
}

void room_destroy(Room *room) {
	if (room == NULL) return;
    	//free(room->tiles);
	
	int i;
	int ports_n = room->ports_n;
	Port **ports = room->ports;
	
	for (i = 0; i < ports_n; ++i)
		port_destroy(ports[i]);

    	free(room);
}
