/*
 * This header file defines CORRIDORS between ROOMS. A CORRIDOR connects
 * two rooms on PORTS.
*/

#ifndef CORRIDOR_H
#define CORRIDOR_H

#include "game/room.h"
#include "game/tile.h"

/*
 * @tiles_n = #tiles on path
 * @port, @port_: two PORTS that the CORRIDOR connects
*/
typedef struct {
	Room *room, *room_;
	int port, port_;
	int tiles_n;
	Tile **tiles;
} Corridor;

Corridor *corridor_create();
void corridor_append_tile(Corridor *corridor, Tile *tile);
void corridor_destroy(Corridor *corridor);

#endif
