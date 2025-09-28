#ifndef MONSTER_H
#define MONSTER_H

#include "../common.h"
#include <ncurses.h>

struct Player;
struct Monster;
struct MonsterTemplate;

typedef struct MonsterTemplate {
    const char *name;
    wchar_t symbol;
    short color_pair;
    int max_hp;
    void (*on_update)(struct Monster *self, struct Player *player);

} MonsterTemplate;

typedef struct Monster {
    int y, x;                   
    int hp;                     
    bool active;               
    
    const MonsterTemplate *template; 
    
    
} Monster;


void monsters_init(void);
void monsters_update_all(void);
void monsters_draw_all(WINDOW *win);

#endif



