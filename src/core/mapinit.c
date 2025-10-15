#include "core/mapinit.h"
#include "core/mapgen.h"
#include "core/enums.h"
#include "core/ui.h"
#include "game/map.h"
#include "game/player.h"
#include <assert.h>

Map *g_world_map = NULL;

void room_draw(Room *room, Map *map) {
	assert(room != NULL);
	assert(map != NULL);

	if (room->explored == 0) {
		printf("%d %d\n", room->x, room->y);
		return;
	}

	int height = room->height, width = room->width;
	int start_x, start_y;
	int i, j;

	room_get_start(room, &start_x, &start_y);

	int H = map->height, W = map->width;
	assert(0 <= start_x && start_x + height < H);
	assert(0 <= start_y && start_y + width < W);

	for (i = 0; i < height; ++i) {
		map_set(map, start_x + i, start_y, TILE_WALL_HOR, 0xff0000, 0x000000);
		map_set(map, start_x + i, start_y + width - 1, TILE_WALL_HOR, 0xff0000, 0x000000);
	}
	for (j = 0; j < width; ++j) {
		map_set(map, start_x, start_y + j, TILE_WALL_VER, 0xff0000, 0x000000);
		map_set(map, start_x + height - 1, start_y + j, TILE_WALL_VER, 0xff0000, 0x000000);
	}
	map_set(map, start_x, start_y, TILE_WALL_COR_LU, 0xff0000, 0x000000);
	map_set(map, start_x, start_y + width - 1, TILE_WALL_COR_RU, 0xff0000, 0x000000);
	map_set(map, start_x + height - 1, start_y, TILE_WALL_COR_LD, 0xff0000, 0x000000);
	map_set(map, start_x + height - 1, start_y + width - 1, TILE_WALL_COR_RD, 0xff0000, 0x000000);

	for (i = 1; i < height - 1; ++i) {
		for (j = 1; j < width - 1; ++j)
			map_set(map, start_x + i, start_y + j, TILE_ROOM, 0xffff00, 0x000000);
	}

	Port **ports = room->ports;
	int ports_n = room->ports_n;
	
	for (i = 0; i < ports_n; ++i) {
		int lrud = ports[i]->LRUD, offset = ports[i]->offset;

		map_set(map, start_x + offset * (lrud < 2) + (height - 1) * (lrud == 3), start_y + offset * (lrud >= 2) + (width - 1) * (lrud == 1), TILE_PORT, 0xff0000, 0x000000);
	}
}

void corridor_draw(Corridor *corridor) {
	int n = corridor->tiles_n;
	Tile **tiles = corridor->tiles;
	int i;

	for (i = 0; i < n; ++i)
		tile_draw(tiles[i], TILE_CORRIDOR, 0x7f7f7f, 0x000000);
}

unsigned char map_layout[MAP_HEIGHT + 1][MAP_WIDTH + 1];
int mapfg[MAP_HEIGHT + 1][MAP_WIDTH+1], mapbg[MAP_HEIGHT+1][MAP_WIDTH+1];

/*
 * Write part of @*map to @map_layout
 * starting from (@x, @y)
*/
void map_write(Map *map, int x, int y) { 
	assert(map != NULL);

	int i, j;

	for (i = 0; i < MAP_HEIGHT; ++i) {
		for (j = 0; j < MAP_WIDTH; ++j) {
			int world_row = i + x;
			int world_col = j + y;

			if (world_row >= 0 && world_row < map->height &&
			    world_col >= 0 && world_col < map->width)
			{
				Tile *tile = map_get_tile(map, world_row, world_col);
				if (tile_display(tile) != LEGENDS[TILE_CORRIDOR] || tile->is_explored) {
					map_layout[i][j] = tile_display(tile);
					mapfg[i][j] = tilefg(tile);
					mapbg[i][j] = tilebg(tile);
				}
				continue;

				if (tile->is_explored) {
					map_layout[i][j] = tile_display(tile);
				} else {
					map_layout[i][j] = TILE_EMPTY;
				}
			} else {
				map_layout[i][j] = TILE_EMPTY;
			}
		}
	}
}

void rooms_draw(Map *map)
{
	Room **rooms = map->rooms;
	int n = map->rooms_n;
	for (int i = 0; i < n; ++i) {
		room_draw(rooms[i], map);
	}
}

void rooms_update_visibility(Map *map)
{
	Room **rooms = map->rooms;
	int n = map->rooms_n;
	for (int i = 0; i < n; ++i) {
		int x = rooms[i]->x, y = rooms[i]->y;
		int w = rooms[i]->width, h = rooms[i]->height;
		int px = player.y, py = player.x;
		if (x <= px+1 && px-1 < x + h && y <= py+1 && py-1 < y + w) {
			rooms[i]->explored = 1;
			for (int u = x; u < x+h; ++u) {
				for (int v = y; v < y+w; ++v) {
					Tile *tile = map_get_tile(map, u, v);
					tile->is_explored = 1;
				}
			}
		}
	}
	rooms_draw(map);
	map_write(map, 0, 0);
}

void map_init(int *hero_x, int *hero_y) {

	g_world_map = bsp_generator(MAP_ROOMS_N, MAP_HEIGHT_ACT, MAP_WIDTH_ACT);
	
	static char s[100];

	sprintf(s, "rooms_n: %d", g_world_map->rooms_n);
	ui_log_message(s);

	int i;

	for (i = 0; i < MAP_HEIGHT; ++i) {
		map_set(g_world_map, i, 0, TILE_WALL, 0xff0000, 0x000000);
		map_set(g_world_map, i, MAP_WIDTH - 1, TILE_WALL, 0xff0000, 0x000000);
	}
	for (i = 0; i < MAP_WIDTH; ++i) {
		map_set(g_world_map, 0, i, TILE_WALL, 0xff0000, 0x000000);
		map_set(g_world_map, MAP_HEIGHT - 1, i, TILE_WALL, 0xff0000, 0x000000);
	}

	Room **rooms = g_world_map->rooms;

	rooms_draw(g_world_map);

	room_get_random_coordinate(rooms[0], hero_x, hero_y);

	Corridor **corridors = g_world_map->corridors;
	int corridors_n = g_world_map->corridors_n;

	for (i = 0; i < corridors_n; ++i)
		corridor_draw(corridors[i]);

	map_write(g_world_map, 0, 0);

}
