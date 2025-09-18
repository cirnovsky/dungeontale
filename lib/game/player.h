#ifndef PLAYER_H
#define PLAYER_H

#include "../common.h"

typedef struct {
    int y, x;
    int target_dx; 
    int target_dy;
    char icon;
    
    int last_move_time; 
} Player;

extern Player player;

void player_init();
void player_draw();
void player_set_move_target(int ch);
void player_update(int game_timer);

#endif
