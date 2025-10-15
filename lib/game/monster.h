#ifndef MONSTER_H
#define MONSTER_H

#include "../common.h"
#include "core/texture.h"
#include "core/ui.h"

#define MAX_MONSTERS 20

struct Player;
struct Monster;
struct MonsterTemplate;

typedef struct MonsterTemplate {
    const char *name;
    wchar_t symbol;
    short color_pair;
    int max_hp;
    int move_speed;
    void (*on_update)(struct Monster *self, struct Player *player);

} MonsterTemplate;

typedef struct Monster {
    int y, x;                   
    int hp;                     
    bool active;
    int move_cooldown;    
    char name[250];           
    
    const MonsterTemplate *template; 
    
    
} Monster;


extern Monster g_monsters[MAX_MONSTERS];

void monsters_init(void);
void monsters_update_all(void);
void monsters_draw_all(WindowArea *win, texture *t, int x, int y);
void monster_die(Monster *monster);
void generate_monster_name(Monster *monster);

#endif



