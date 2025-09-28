#ifndef PATH_H
#define PATH_H

#include "game/map.h"
#include "game/tile.h"

Tile **path_find(Map *map, int x1, int y1, int x2, int y2, int hv, int *cnt);

#endif
