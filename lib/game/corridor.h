/*
 * This header file defines CORRIDORS between ROOMS. A CORRIDOR connects
 * two rooms on PORTS.
*/

#include "room.h"

/*
 * @length = #tiles on @path
 * @port, @port_: two PORTS that the CORRIDOR connects
*/
typedef struct {
	int length;
	Port *port, *port_;
	Tile *path;
} Corridor;

Corridor corridor_create(Room *room, Room *room_) {
	Corridor *corridor = malloc(sizeof(Corridor));
	corridor->room = room;
	corridor->room_ = room_;
}
