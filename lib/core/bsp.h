#ifndef BSP_H
#define BSP_H

#include "game/map.h"
#include "game/room.h"
#include "game/corridor.h"

typedef struct BSPNode {
	struct BSPNode *lchild, *rchild;
	Room *room; // for leaf nodes only
	Corridor *corridor;
	Room *L, *R, *U, *D;
	int HV, port;
} BSPNode;

BSPNode *BSPNode_create(Room *room);
void BSPNode_destroy(BSPNode *node);
BSPNode *bsp_tree(int h, int w, int x, int y, int min_h, int min_w, int *count_rooms);
int bsp_is_leaf(BSPNode *node);

#endif
