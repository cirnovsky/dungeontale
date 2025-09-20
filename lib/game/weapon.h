#ifndef WEAPON_H
#define WEAPON_H

#include "../common.h"

typedef struct {
    int width;
    int length;
    int weight;
} Weapon;

void hitbox_init();

void hitbox_create(int y, int x, int h, int w, int lifetime);

void hitbox_update_all();

void hitbox_draw_all(WINDOW *win);


#endif
