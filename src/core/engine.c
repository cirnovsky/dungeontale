#include "core/engine.h"
#include "core/ui.h"
#include "game/player.h"
#include "game/map.h"
#include "core/renderer.h"
#include "game/monster.h"
#include "core/mapinit.h"
#include "game/hitbox.h"
#include <unistd.h> 


void engine_init() {
    ui_init();
    renderer_init();
    player_init();
    nodelay(stdscr, TRUE);
    map_init();
    monsters_init();
    hitbox_init(); 
    ui_log_message("Use arrow keys to move.");
    ui_log_message("Press 'q' to quit.");
    int number_of_ball = 0;
    ui_log_message("Wgy has %d balls.", number_of_ball);
}

void engine_run() {
    int ch;
    int game_timer = 0; 

    while (true) {
        game_timer++; 

        ch = getch();
        if (ch == 'a') {
            player_attack();
        }
        if (ch == 'q') {
            break;
        }
        if (ch == KEY_RESIZE) {
            handle_resize();
        }
        player_set_move_target(ch); 

        ui_draw();

        if (player.attack_cooldown > 0) {
            player.attack_cooldown--;
        }
        hitbox_update_all(); 
        player_update(game_timer);
        monsters_update_all();
        
        usleep(30000);
    }
}

void handle_resize(){
    ui_recreate_windos();
    clear();
    refresh();
    ui_draw();
}

void engine_shutdown() {
	//map_destroy(g_world_map);
    ui_shutdown();
}
