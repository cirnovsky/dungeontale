#define _DEFAULT_SOURCE 
#include "core/engine.h"
#include "core/ui.h"
#include "game/player.h"
#include <unistd.h> 

void engine_init() {
    ui_init();
    player_init();
    nodelay(stdscr, TRUE); 
    ui_log_message("Use arrow keys to move.");
    ui_log_message("Press 'q' to quit.");
}

void engine_run() {
    int ch;
    int game_timer = 0; 

    while (true) {
        game_timer++; 

        ch = getch();
        if (ch == 'q') {
            break; 
        }
        
        player_set_move_target(ch);

        player_update(game_timer);
        
        ui_draw();

        usleep(30000); 
    }
}

void engine_shutdown() {
    ui_shutdown();
}
