#include "core/bsp.h"
#include "core/rng.h"
#include <stdlib.h>
#include <assert.h>

BSPNode *BSPNode_create(Room *room) {
	BSPNode *node = malloc(sizeof(BSPNode));
	
	node->lchild = node->rchild = NULL;
	node->room = room;
	return node;
}

void BSPNode_destroy(BSPNode *node) {
	if (node == NULL)
		return;
	free(node->lchild);
	free(node->rchild);
	free(node->room);
	free(node);
}

BSPNode *bsp_tree(int h, int w, int x, int y, int min_h, int min_w, int *count_rooms) {
	BSPNode *node = BSPNode_create(NULL);

	if (h / 2 < min_h && w / 2 < min_w) {
		node->room = room_create(h - 1, w - 1, x, y);
		assert(node->room->height == h - 1);
		assert(node->room->width == w - 1);
		(*count_rooms)++;
		return node;
	}

	int orientation = rng_range(0, 2);

	if (orientation || w / 2 < min_w) {
		assert(h / 2 >= min_h);
		node->lchild = bsp_tree(h / 2, w, x, y, min_h, min_w, count_rooms);
		node->rchild = bsp_tree((h + 1) / 2, w, x, y + w / 2, min_h, min_w, count_rooms);
	} else {
		assert(w / 2 >= min_w);
		node->lchild = bsp_tree(h, w / 2, x, y, min_h, min_w, count_rooms);
		node->rchild = bsp_tree(h, (w + 1) / 2, x + h / 2, y, min_h, min_w, count_rooms);
	}

	return node;
}
