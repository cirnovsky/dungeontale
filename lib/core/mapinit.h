#ifndef MAPINIT_H
#define MAPINIT_H

#include "core/enums.h"
#include "game/map.h"

extern wchar_t map_layout[MAP_HEIGHT + 1][MAP_WIDTH + 1];
void map_init(int *hero_x, int *hero_y);
void map_write(Map *map, int x, int y);

#endif
