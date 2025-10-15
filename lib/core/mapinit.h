#ifndef MAPINIT_H
#define MAPINIT_H

#include "core/enums.h"
#include "game/map.h"

extern unsigned char map_layout[MAP_HEIGHT + 1][MAP_WIDTH + 1];
extern int mapfg[MAP_HEIGHT + 1][MAP_WIDTH+1], mapbg[MAP_HEIGHT+1][MAP_WIDTH+1];
void map_init(int *hero_x, int *hero_y);
void map_write(Map *map, int x, int y);
void rooms_update_visibility(Map *map);

#endif
