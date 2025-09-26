#include "game/monster.h"
#include "game/monster_ai.h" 
#include "game/player.h"
#include "core/renderer.h"
#include "time.h"

static const MonsterTemplate GOBLIN_TEMPLATE = {
    .name = "Goblin",
    .symbol = L'g',
    .color_pair = COLOR_GREEN,
    .max_hp = 10,
    .on_update = &ai_behavior_chase_player 
};

static const MonsterTemplate BAT_TEMPLATE = {
    .name = "Bat",
    .symbol = L'b',
    .color_pair = COLOR_YELLOW,
    .max_hp = 5,
    .on_update = &ai_behavior_move_randomly 
};


#define MAX_MONSTERS 20
static Monster g_monsters[MAX_MONSTERS]; 

void monster_spawn(const MonsterTemplate *template, int y, int x) {
    for (int i = 0; i < MAX_MONSTERS; ++i) {
        if (!g_monsters[i].active) {
            g_monsters[i].active = true;
            g_monsters[i].y = y;
            g_monsters[i].x = x;
            g_monsters[i].hp = template->max_hp;
            g_monsters[i].template = template; 
            return;
        }
    }
}

void monsters_init(void) {
    srand(time(NULL)); 

    for (int i = 0; i < MAX_MONSTERS; ++i) {
        g_monsters[i].active = false;
    }
    
    int num_goblins_to_spawn = 5;
    for (int i = 0; i < num_goblins_to_spawn; ++i) {
        int monster_y;
        int monster_x;
        do {
            monster_y = rand() % 80;
    // monster_spawn(&BAT_TEMPLATE, valid_y, valid_x);
            monster_x = rand() % 80;
        } while (!map_is_walkable(monster_y, monster_x)); 

        monster_spawn(&GOBLIN_TEMPLATE, monster_y, monster_x);
    }
    int num_bats_to_spawn = 5;
    for (int i = 0; i < num_bats_to_spawn; ++i) {
        
        int monster_y;
        int monster_x;
        do {
            monster_y = rand() % 80;
            monster_x = rand() % 80;
        } while (!map_is_walkable(monster_y, monster_x)); 

        monster_spawn(&BAT_TEMPLATE, monster_y, monster_x);
    }
    
}

void monsters_update_all(void) {
    for (int i = 0; i < MAX_MONSTERS; ++i) {
        if (g_monsters[i].active) {
            Monster *monster = &g_monsters[i];
            if (monster->template->on_update) {
                monster->template->on_update(monster, &player); 
            }
        }
    }
}
void monsters_draw_all(WINDOW *win) {
    for (int i = 0; i < MAX_MONSTERS; ++i) {
        if (g_monsters[i].active) {
            Monster *m = &g_monsters[i];
            
            Sprite monster_sprite = {
                .symbol = m->template->symbol,
                .fg_color = m->template->color_pair,
                .bg_color = -1,
                .attributes = A_NORMAL
            };
            
            renderer_draw_sprite(win, m->y + 1, m->x + 1, &monster_sprite);
        }
    }
}
