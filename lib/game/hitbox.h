#ifndef HITBOX_H
#define HITBOX_H

#include "../common.h"

#define MAX_HITBOXES 10

typedef struct{
    int x, y;
    int width, height;
    int lifetime;
    bool active;
} Hitbox;


extern Hitbox g_hitboxes[MAX_HITBOXES];


#endif

