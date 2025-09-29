#include <locale.h>
#include "game/player.h"
#include "game/weapon.h"
#include "game/hitbox.h"
#include "core/renderer.h"
#include "game/map.h"
#include "core/ui.h"
#include <stdio.h>

#define PLAYER_MOVE_COOLDOWN 1

Player player;

static Weapon cirnov_dagger = {
    .attack_sweep = 1,
    .attack_reach = 2,
    .weight = 1,
    .name = "cirnov's tiny dagger"
};


void player_init(){
    player.y = 5;
    player.x = 5;
    player.target_dx = 0; 
    player.target_dy = 0;
    player.last_move_dx = 0;
    player.last_move_dy = 1; 
    player.attack_cooldown = 5;
    player.last_move_time = 0; 
    player.equipped_weapon = &cirnov_dagger;
    player.attack_cooldown = 0;
}

void player_draw(WINDOW *win){

    Sprite player_sprite = {
        .symbol = L'@',
        .fg_color = COLOR_YELLOW,
        .bg_color = -1,
        .attributes = A_BOLD
    };

    renderer_draw_sprite(win, player.y + 1, player.x + 1, &player_sprite);
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
            player.last_move_dx = player.target_dx; 
            player.last_move_dy = player.target_dy;
        } else {
            ui_log_message("Player bumps into a wall.");
        }
        
        player.last_move_time = game_timer;
    }
    
}
void player_attack() {
    if (player.attack_cooldown > 0) {
        ui_log_message("Attack is on cooldown.");
        return;
    }
    if (player.equipped_weapon == NULL) {
        ui_log_message("You have no weapon equipped.");
        return;
    }

    int length = player.equipped_weapon->attack_reach; 
    int width = player.equipped_weapon->attack_sweep;   

    for (int i = 1; i <= length; i++) { 
        bool wall_was_hit = false;
        
        int slice_y, slice_x, slice_h, slice_w;

        if (player.last_move_dy != 0) { 
            slice_h = 1;
            slice_w = width; 
            slice_y = player.y + (i * player.last_move_dy);
            slice_x = player.x - (width / 2); 
        } else { 
            slice_h = width; 
            slice_w = 1;
            slice_y = player.y - (width / 2); 
            slice_x = player.x + (i * player.last_move_dx);
        }

        for (int j = 0; j < slice_h; j++) {
            for (int k = 0; k < slice_w; k++) {
                int check_y = slice_y + j;
                int check_x = slice_x + k;
                if (!map_is_walkable(check_y, check_x)) {
                    wall_was_hit = true;
                    break;
                }
            }
            if (wall_was_hit) break;
        }

        if (wall_was_hit) {
            ui_log_message("Attack was blocked by a wall.");
            break;
        } else {
            hitbox_create(slice_y, slice_x, slice_h, slice_w, 3);
        }
    }
    player.attack_cooldown = 5;
}
