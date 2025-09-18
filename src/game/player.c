#include "game/player.h"
#include "game/map.h"
#include "core/ui.h"

#define PLAYER_MOVE_COOLDOWN 3

Player player;

void player_init(){
    player.y = 5;
    player.x = 5;
    player.target_dx = 0; 
    player.target_dy = 0;
    player.icon = '@';    
    player.last_move_time = 0; 
}

void player_draw(){
    mvwaddch(win_main, player.y + 1, player.x + 1, player.icon);
}

void player_set_move_target(int ch){
    switch (ch) {
        case KEY_UP:    player.target_dy = -1; player.target_dx = 0; break;
        case KEY_DOWN:  player.target_dy = 1;  player.target_dx = 0; break;
        case KEY_LEFT:  player.target_dx = -1; player.target_dy = 0; break;
        case KEY_RIGHT: player.target_dx = 1;  player.target_dy = 0; break;
        default:
            player.target_dx = 0;
            player.target_dy = 0;
            break;
    }
}

void player_update(int game_timer) {
    if ((player.target_dx != 0 || player.target_dy != 0) &&
        (game_timer - player.last_move_time >= PLAYER_MOVE_COOLDOWN)) {
        
        int next_y = player.y + player.target_dy;
        int next_x = player.x + player.target_dx;

        if (map_is_walkable(next_y, next_x)){
            player.y = next_y;
            player.x = next_x;
            ui_log_message("Player moves.");
        } else {
            ui_log_message("Player bumps into a wall.");
        }
        
        player.last_move_time = game_timer;
    }
    
}
