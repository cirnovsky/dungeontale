#ifndef PLAYER_H
#define PLAYER_H

#include "../common.h"
#include "game/weapon.h"


typedef struct {
    int y, x;
    int target_dx; 
    int target_dy;
    char icon;
    int last_move_dx;
    int last_move_dy;
    int attack_cooldown;
    int last_move_time;
    int fov_radius;
    Weapon *equipped_weapon;
} Player;

extern Player player;

void player_init();
void player_draw(WINDOW *win);
void player_set_move_target(int ch);
void player_update(int game_timer);
void player_attack();

#endif
