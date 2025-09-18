#include "core/ui.h"
#include "game/map.h"
#include "game/player.h"

WINDOW *win_main;
WINDOW *win_log;

void ui_init() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    int term_h, term_w;
    getmaxyx(stdscr, term_h, term_w);

    win_main = newwin(term_h - 10, term_w, 0, 0);
    win_log = newwin(10, term_w, term_h - 10, 0);
    
    scrollok(win_log, TRUE);
    
    refresh();
}

void ui_shutdown() {
    delwin(win_main);
    delwin(win_log);
    endwin();
}

void ui_draw() {
    werase(win_main); 

    box(win_main, 0, 0);
    box(win_log, 0, 0);
    mvwprintw(win_log, 0, 2, " Battle Log ");
    
    map_draw();
    player_draw();
    
    wrefresh(win_main);
    wrefresh(win_log);
}

void ui_log_message(const char *message) {
    int log_h, log_w;
    getmaxyx(win_log, log_h, log_w); 

    wscrl(win_log, 1);

    mvwprintw(win_log, log_h - 2, 2, " > %.*s", log_w - 4, message);

    box(win_log, 0, 0);
    mvwprintw(win_log, 0, 2, " Battle Log ");

    wrefresh(win_log);
}

