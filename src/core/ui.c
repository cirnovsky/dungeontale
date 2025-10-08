#define _XOPEN_SOURCE_EXTENDED 1
#include "core/ui.h"
#include "core/mapinit.h"
#include "core/enums.h"
#include "game/player.h"
#include "game/hitbox.h"
#include "game/monster.h"
#include <locale.h>
#include <ncurses.h>
#include <stdarg.h>
#include <stdio.h>
#include "game/monster.h"
#include "game/map.h"

WINDOW *win_main;
WINDOW *win_log;

void map_draw(){
    for (int y = 0; y < MAP_HEIGHT; ++y)
        mvwaddwstr(win_main, y+1, 1, map_layout[y]);
}

void ui_init() {
	setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    int term_h, term_w;
    getmaxyx(stdscr, term_h, term_w);

    win_main = newwin(term_h, term_w, 0, term_w / 5);
    win_log = newwin(term_h / 3, term_w / 5, 0, 0);
    
    scrollok(win_log, TRUE);
    
    refresh();
}

void ui_recreate_windos() {
    if (win_main) delwin(win_main);
    if (win_log) delwin(win_log);

    int term_h, term_w;
    getmaxyx(stdscr, term_h, term_w);

    win_main = newwin(term_h, term_w - term_w/5, 0, term_w / 5);
    win_log = newwin(term_h / 3, term_w / 5, 0, 0);
    scrollok(win_log, TRUE);
    keypad(win_main, TRUE);

}

void ui_shutdown() {
    delwin(win_main);
    delwin(win_log);
    endwin();
}

void ui_draw() {
    werase(win_main);

    box(win_main, 0 , 0);
    box(win_log, 0, 0);
    mvwprintw(win_log, 0, 2, " Battle Log ");

    map_write(g_world_map, 0, 0);

    map_draw();

    hitbox_draw_all(win_main);
    monsters_draw_all(win_main);
    player_draw(win_main);


    



    wrefresh(win_main);
    wrefresh(win_log);
}

void ui_log_message(const char *format, ...) {

    char formatted_message[512];
    va_list args;

    va_start(args, format);
    vsnprintf(formatted_message, sizeof(formatted_message), format, args);
    va_end(args);


    int log_h, log_w;
    getmaxyx(win_log, log_h, log_w);
    int content_w = log_w - 2;

    char *msg_copy = strdup(formatted_message);
    if (!msg_copy) return;

    wscrl(win_log, 1);
    wmove(win_log, log_h - 2, 1);
    wprintw(win_log, "> ");

    char *word = strtok(msg_copy, " ");
    while (word != NULL) {
        if (getcurx(win_log) + (int)strlen(word) + 1 > content_w) {
            wscrl(win_log, 1); 
            wmove(win_log, log_h - 2, 1); 
            wprintw(win_log, "  "); 
        }

        wprintw(win_log, "%s ", word);
        
        word = strtok(NULL, " ");
    }
    
    free(msg_copy);

    box(win_log, 0, 0);
    mvwprintw(win_log, 0, 2, " Battle Log ");
    wrefresh(win_log);
}
