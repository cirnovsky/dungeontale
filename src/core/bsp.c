#include "core/bsp.h"
#include "core/rng.h"
#include "core/path.h"
#include <stdlib.h>
#include <assert.h>

BSPNode *BSPNode_create(Room *room) {
	BSPNode *node = malloc(sizeof(BSPNode));
	
	node->lchild = node->rchild = NULL;
	node->corridor = NULL;
	node->room = room;
	node->HV = 0;
	node->L = node->R = node->U = node->D = NULL;
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

int bsp_is_leaf(BSPNode *node) {
	if (node == NULL)
		return 0;

	if (node->lchild == NULL || node->rchild == NULL)
		assert(node->lchild == NULL && node->rchild == NULL);

	return node->lchild == NULL;
}

BSPNode *bsp_tree(int h, int w, int x, int y, int min_h, int min_w, int *count_rooms) {
	BSPNode *node = BSPNode_create(NULL);

	if (h / 2 < min_h && w / 2 < min_w) {
		int h_ = rng_range(4, h);
		int w_ = rng_range(4, w);

		node->room = room_create(h_, w_, x, y);
		node->L = node->R = node->U = node->D = node->room;
		(*count_rooms)++;
		return node;
	}

	int orientation = rng_range(0, 2);

	if ((orientation && h / 2 >= min_h) || w / 2 < min_w) {
		node->HV = 1;
		assert(h / 2 >= min_h);
		node->lchild = bsp_tree(h / 2, w, x, y, min_h, min_w, count_rooms);
		node->rchild = bsp_tree((h + 1) / 2, w, x + h / 2, y, min_h, min_w, count_rooms);
	} else {
		node->HV = 0;
		assert(w / 2 >= min_w);
		node->lchild = bsp_tree(h, w / 2, x, y, min_h, min_w, count_rooms);
		node->rchild = bsp_tree(h, (w + 1) / 2, x, y + w / 2, min_h, min_w, count_rooms);
	}

	BSPNode *lc = node->lchild, *rc = node->rchild;

	node->L = lc->L;
	node->R = rc->L;
	node->U = lc->U;
	node->D = rc->D;

	if (bsp_is_leaf(lc) || bsp_is_leaf(rc)) {
		assert(bsp_is_leaf(lc) && bsp_is_leaf(rc));

		node->corridor = corridor_create();
	}

	return node;
}
