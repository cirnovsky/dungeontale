#include "core/fov.h"
#include "game/player.h"
#include "game/map.h"

bool g_fov_enabled = true;

extern Player player;
extern Map* g_world_map;



void fov_show_all(void) {
    if (!g_world_map) return;
    for (int i = 0; i < g_world_map->height * g_world_map->width; ++i) {
        g_world_map->tiles[i]->is_visible = true;
        g_world_map->tiles[i]->is_explored = true;
    }
}


void fov_update(void) {
    if (!g_fov_enabled) {
        fov_show_all();
        return;
    }

    if (!g_world_map) return;

    for (int y = player.y - player.fov_radius; y <= player.y + player.fov_radius; ++y) {
        for (int x = player.x - player.fov_radius; x <= player.x + player.fov_radius; ++x) {

            if (y >= 0 && y < g_world_map->height && x >= 0 && x < g_world_map->width) {
                Tile *tile = map_get_tile(g_world_map, y, x); 
                if (tile) {
                    tile->is_explored = true;
                }
            }
        }
    }
}
