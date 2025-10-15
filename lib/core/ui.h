#ifndef UI_H
#define UI_H

#include "../common.h"
#include "core/engine.h"

typedef struct {
	int x, y, w, h;
} WindowArea;

WindowArea *mynewwin(int x, int y, int w, int h);

extern WindowArea *win_main;
extern WindowArea *win_log;

void ui_init();
void ui_shutdown();
void ui_draw(Engine *engine);
void ui_recreate_windos();
void ui_log_message(const char* format, ...);
int ui_get_input();

#endif
