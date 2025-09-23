#include "core/mapinit.h"
#include "core/mapgen.h"
#include "core/enums.h"
#include "core/ui.h"
#include "game/map.h"
#include <assert.h>
#include <ncurses.h>

Map *g_world_map = NULL;

void room_draw(Room *room, Map *map) {
	assert(room != NULL);
	assert(map != NULL);

	int height = room->height, width = room->width;
	int start_x, start_y;
	int i, j;

	room_get_start(room, &start_x, &start_y);

	int H = map->height, W = map->width;
	assert(0 <= start_x && start_x + height < H);
	assert(0 <= start_y && start_y + width < W);

	for (i = 0; i < height; ++i) {
		map_set(map, start_x + i, start_y, TILE_WALL_HOR);
		map_set(map, start_x + i, start_y + width - 1, TILE_WALL_HOR);
	}
	for (j = 0; j < width; ++j) {
		map_set(map, start_x, start_y + j, TILE_WALL_VER);
		map_set(map, start_x + height - 1, start_y + j, TILE_WALL_VER);
	}
	map_set(map, start_x, start_y, TILE_WALL_COR_LU);
	map_set(map, start_x, start_y + width - 1, TILE_WALL_COR_RU);
	map_set(map, start_x + height - 1, start_y, TILE_WALL_COR_LD);
	map_set(map, start_x + height - 1, start_y + width - 1, TILE_WALL_COR_RD);
}

wchar_t map_layout[MAP_HEIGHT + 1][MAP_WIDTH + 1];

/*
 * Write part of @*map to @map_layout
 * starting from (@x, @y)
*/
void map_write(Map *map, int x, int y) {
	assert(map != NULL);

	int i, j;

	for (i = 0; i < MAP_HEIGHT; ++i) {
		for (j = 0; j < MAP_WIDTH; ++j) {
			Tile *tile = map_get_tile(map, i + x, j + y);

			map_layout[i][j] = tile_display(tile);
			//if (tile->code == TILE_WALL_HOR)
				//map_layout[i][j] = 0x
		}
		map_layout[i][MAP_WIDTH] = '\0';
	}
}

void map_init() {

	g_world_map = bsp_generator(MAP_ROOMS_N, MAP_HEIGHT_ACT, MAP_WIDTH_ACT);
	
	static char s[114514];

	sprintf(s, "rooms_n: %d", g_world_map->rooms_n);
	ui_log_message(s);

	int i;

	for (i = 0; i < MAP_HEIGHT; ++i) {
		map_set(g_world_map, i, 0, TILE_WALL);
		map_set(g_world_map, i, MAP_WIDTH - 1, TILE_WALL);
	}
	for (i = 0; i < MAP_WIDTH; ++i) {
		map_set(g_world_map, 0, i, TILE_WALL);
		map_set(g_world_map, MAP_HEIGHT - 1, i, TILE_WALL);
	}

	Room **rooms = g_world_map->rooms;
	int rooms_n = g_world_map->rooms_n;

	for (i = 0; i < rooms_n; ++i)
		room_draw(rooms[i], g_world_map);

	map_write(g_world_map, 0, 0);
}
