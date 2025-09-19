#ifndef UI_H
#define UI_H

#include "../common.h"

extern WINDOW *win_main;
extern WINDOW *win_log;

void ui_init();
void ui_shutdown();
void ui_draw();
void ui_recreate_windos();
void ui_log_message(const char* message);

#endif
