#ifndef WEAPON_H
#define WEAPON_H

#include "../common.h"

typedef struct {
    int attack_reach;
    int attack_sweep;
    int weight;
    const char *name;
} Weapon;

void hitbox_init();

void hitbox_create(int y, int x, int h, int w, int lifetime);

void hitbox_update_all();

void hitbox_draw_all(WINDOW *win);


#endif
