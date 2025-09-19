#include "core/engine.h"
#include "core/ui.h"
#include "game/player.h"
#include "core/renderer.h"
#include <unistd.h> 


void engine_init() {
    ui_init();
    renderer_init();
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
        if (ch == KEY_RESIZE) {
            handle_resize();
        }

        if (ch == 'q') {
            break; 
        }
        
        player_set_move_target(ch);

        player_update(game_timer);
        
        ui_draw();

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
    ui_shutdown();
}
