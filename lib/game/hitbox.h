#ifndef HITBOX_H
#define HITBOX_H

#include "../common.h"

typedef struct{
    int x, y;
    int width, height;
    int lifetime;
    bool active;
} Hitbox;

#endif

