#ifndef BSP_H
#define BSP_H

#include "game/map.h"
#include "game/room.h"

typedef struct BSPNode {
	struct BSPNode *lchild, *rchild;
	Room *room; // for leaf nodes only
} BSPNode;

BSPNode *bsp_tree(int h, int w, int x, int y, int min_h, int min_w, int *count_rooms);

#endif
