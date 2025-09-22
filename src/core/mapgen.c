#include "core/mapgen.h"
#include "core/rng.h"
#include "core/bsp.h"
#include <assert.h>

/*
 * @rooms_n = the expected no. of rooms under @map
 * 		if it is too big for the given @height and @width,
 * 		there will be fewer than expected
*/
Map *bsp_generator(int rooms_n, int height, int width) {
	int max_n = height / 2;

	if (width / 2 < max_n)
		max_n = width / 2;
	if (max_n < rooms_n)
		rooms_n = max_n;

	int min_height = height / rooms_n;
	int min_width = width / rooms_n;
	int count_rooms = 0;

	rng_seed(114514); // 114514 is dummy
	BSPNode *root = bsp_tree(height, width, 0, 0, min_height, min_width, &count_rooms);

	Map *map = map_create(count_rooms, height, width);
	int success = 0;

	bsp_flat(root, map->rooms, &success);
	assert(success == count_rooms);
	
	return map;
}

void bsp_flat(BSPNode *node, Room *rooms[], int *cnt) {
	if (node == NULL)
		return;

	bsp_flat(node->lchild, rooms, cnt);
	
	if (node->room != NULL)
		rooms[(*cnt)++] = node->room;

	bsp_flat(node->rchild, rooms, cnt);
}
