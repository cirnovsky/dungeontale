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
    .attack_sweep = 3,
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
    player.attack_cooldown = 0;
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
        ui_log_message("Attack is on cooldown");
        return; 
    }

    if (player.equipped_weapon == NULL) {
        return;
    }

    player.attack_cooldown = 30; 

    int hitbox_y = player.y;
    int hitbox_x = player.x;
    int reach = player.equipped_weapon->attack_reach; 
    int sweep = player.equipped_weapon->attack_sweep;
    int hitbox_h, hitbox_w;

    if (player.last_move_dy != 0) {
        hitbox_h = reach; 
        hitbox_w = sweep; 
    } else { 
        hitbox_h = sweep; 
        hitbox_w = reach; 
    }


    if (player.last_move_dy == -1){
        hitbox_y = player.y - hitbox_h;
        hitbox_x = player.x - (hitbox_w / 2);
    } else if (player.last_move_dy == 1){
        hitbox_y = player.y + 1;
        hitbox_x = player.x - (hitbox_h / 2);
    } else if (player.last_move_dx == -1){
        hitbox_y = player.y - (hitbox_h / 2);
        hitbox_x = player.x - hitbox_w;
    } else if (player.last_move_dx == 1){
        hitbox_y = player.y - (hitbox_h / 2);
        hitbox_x = player.x + 1;
    }




    hitbox_create(hitbox_y, hitbox_x, hitbox_h, hitbox_w, 3);


    char log_buffer[128];
    snprintf(log_buffer, sizeof(log_buffer), "Slashing with %s.",player.equipped_weapon->name);
    ui_log_message(log_buffer);
}
