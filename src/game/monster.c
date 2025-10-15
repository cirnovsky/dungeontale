#include "game/monster.h"
#include "game/monster_ai.h" 
#include "game/player.h"
#include "game/map.h"
#include "core/ui.h"
#include "core/renderer.h"
#include "time.h"

//static const char* GOBLIN_FIRST_NAMES[] = {"猥琐的", "发育不良的", "扭曲的", "浮肿的", "骸骨的", "甲壳的", "胶状的", "暴虐的", "腐烂的", "化脓的", "被诅咒的", "染病的", "无魂的", "炉管的", "好色的", "阳痿的"};
static const char* GOBLIN_FIRST_NAMES[] = {
	#include "assets/text/gobfn.c"
};
static const char* BAT_FIRST_NAMES[] = {"Suspicious"};



static const MonsterTemplate GOBLIN_TEMPLATE = {
    .name = "Malon",
    .symbol = 'g',
    .color_pair = COLOR_GREEN,
    .max_hp = 10,
    .move_speed = 10,
    .on_update = &ai_behavior_chase_player 
};

static const MonsterTemplate BAT_TEMPLATE = {
    .name = "Bat",
    .symbol = 'b',
    .color_pair = COLOR_YELLOW,
    .max_hp = 5,
    .move_speed = 5,
    .on_update = &ai_behavior_move_randomly 
};


Monster g_monsters[MAX_MONSTERS]; 

void monster_spawn(const MonsterTemplate *template, int y, int x) {
    for (int i = 0; i < MAX_MONSTERS; ++i) {
        if (!g_monsters[i].active) {
            Monster *new_monster = &g_monsters[i];

            g_monsters[i].active = true;
            g_monsters[i].y = y;
            g_monsters[i].x = x;
            g_monsters[i].hp = template->max_hp;
            g_monsters[i].template = template;
            g_monsters[i].move_cooldown = template->move_speed;

            generate_monster_name(new_monster);

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

            monster->move_cooldown--;

            if (monster->move_cooldown <= 0){

                if (monster->template->on_update) {
                    monster->template->on_update(monster, &player); 
                }
                monster->move_cooldown = monster->template->move_speed;
            }    
        }
    }
}
void monsters_draw_all(WindowArea *win, texture *t, int x, int y) {
    for (int i = 0; i < MAX_MONSTERS; ++i) {
        if (g_monsters[i].active) {
            Monster *m = &g_monsters[i];
           
            Tile *tile_under_monster = map_get_tile(g_world_map, m->y, m->x);

            if (!tile_under_monster->is_explored) {
                continue;
            }

            Sprite monster_sprite = {
                .symbol = m->template->symbol,
                .fg_color = m->template->color_pair,
                .bg_color = -1,
                .attributes = A_NORMAL
            };
            
            renderer_draw_sprite(win, t, m->y - x + 1, m->x - y + 1, &monster_sprite);
        }
    }
}

void monster_die(Monster *monster){
    if (!monster->active) return;

    monster->active = false;

    ui_log_message("%s  has been slayed!", monster->name);    

}

void generate_monster_name(Monster *monster) {
    const char* first_name = "Nameless";
    const char* species_name = monster->template->name;

    if (strcmp(species_name, "Malon") == 0) {
        int name_count = sizeof(GOBLIN_FIRST_NAMES) / sizeof(GOBLIN_FIRST_NAMES[0]);
        first_name = GOBLIN_FIRST_NAMES[rand() % name_count];
    } else if (strcmp(species_name, "Bat") == 0) {
        int name_count = sizeof(BAT_FIRST_NAMES) / sizeof(BAT_FIRST_NAMES[0]);
        first_name = BAT_FIRST_NAMES[rand() % name_count];
    }

    snprintf(monster->name, sizeof(monster->name), "%s %s", first_name, species_name);
}
