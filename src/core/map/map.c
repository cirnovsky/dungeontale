#include "map.h"
#include <stdlib.h>

Map *map_create(int n) {
	Map *map = malloc(sizeof(Map));
	map->rooms_n = n;
	map->rooms = calloc(n, sizeof(Room));
	return map;
}

void map_destroy(Map *map) {
	free(map->rooms);
	free(map);
}
