#include "core/mapgen.h"
#include "core/rng.h"
#include "core/bsp.h"
#include "core/utils.h"
#include "core/ui.h"
#include <assert.h>
#include <math.h>

void bsp_flat(BSPNode *node, Room *rooms[], int *cnt) {
	if (node == NULL)
		return;

	bsp_flat(node->lchild, rooms, cnt);
	
	if (bsp_is_leaf(node)) {
		assert(node->room != NULL);
		rooms[(*cnt)++] = node->room;
	}

	bsp_flat(node->rchild, rooms, cnt);
}

Corridor *gen_corridor(Map *map, Room *room, Room *room_, int port, int port_, int hv) {
	assert(room != NULL);
	assert(room_ != NULL);
	
	int rooms_n = room->ports_n, rooms_n_ = room_->ports_n;

	assert(0 <= port && port < rooms_n);
	assert(0 <= port_ && port_ < rooms_n_);

	int x1, y1, x2, y2;

	room_get_port_coordinate(room, port, &x1, &y1);
	room_get_port_coordinate(room_, port_, &x2, &y2);

	int mx = (x1 + x2) / 2, my = (y1 + y2) / 2;
	int i, j, tmp;
	Corridor *corridor = corridor_create();

	if (hv) {
		if (x1 > x2) {
			tmp = x1, x1 = x2, x2 = tmp;
			tmp = y1, y1 = y2, y2 = tmp;
		}
		for (i = x1 + 1; i < mx; ++i)
			corridor_append_tile(corridor, map_get_tile(map, i, y1));
		for (i = mx; i < x2; ++i)
			corridor_append_tile(corridor, map_get_tile(map, i, y2));
		for (j = min(y1, y2); j <= max(y1, y2); ++j)
			corridor_append_tile(corridor, map_get_tile(map, mx, j));
	} else {
		if (y1 > y2) {
			tmp = y1, y1 = y2, y2 = tmp;
			tmp = x1, x1 = x2, x2 = tmp;
		}
		for (i = y1 + 1; i < my; ++i)
			corridor_append_tile(corridor, map_get_tile(map, x1, i));
		for (i = my; i < y2; ++i)
			corridor_append_tile(corridor, map_get_tile(map, x2, i));
		for (j = min(x1, x2); j <= max(x1, x2); ++j)
			corridor_append_tile(corridor, map_get_tile(map, j, my));
	}

	return corridor;
}

int cmp(const void *a, const void *b) {
	const Room *room = *(const Room * const *) a, *room_ = *(const Room * const *) b;

	int x1, y1, x2, y2;

	room_get_start(room, &x1, &y1);
	room_get_start(room_, &x2, &y2);

	if (x1 != x2)
		return x1 - x2;
	return y1 - y2;
}

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
	BSPNode *root = bsp_tree(height - 1, width - 1, 1, 1, min_height, min_width, &count_rooms);

	Map *map = map_create(count_rooms, height, width);
	int success = 0;


	bsp_flat(root, map->rooms, &success);
	assert(success == count_rooms);

	qsort(map->rooms, map->rooms_n, sizeof(Room *), cmp);

	int n = sqrt(count_rooms);
	int i, j;
	Room **rooms = map->rooms;

	for (i = 0; i < n; ++i) {
		for (j = 0; j + 1 < n; ++j) {
			room_set_port_middle(rooms[i * n + j], 1);
			room_set_port_middle(rooms[i * n + j + 1], 0);
			map_append_corridor(map, gen_corridor(map, rooms[i * n + j], rooms[i * n + j + 1], rooms[i * n + j]->ports_n - 1, rooms[i * n + j + 1]->ports_n - 1, 0));
		}
		if (i + 1 == n)
			continue;
		j = (i & 1) ? 0 : n - 1;
		room_set_port_middle(rooms[i * n + j], 3);
		room_set_port_middle(rooms[(i + 1) * n + j], 2);
		map_append_corridor(map, gen_corridor(map, rooms[i * n + j], rooms[(i + 1) * n + j], rooms[i * n + j]->ports_n - 1, rooms[(i + 1) * n + j]->ports_n - 1, 1));
	}

	
	return map;
}
