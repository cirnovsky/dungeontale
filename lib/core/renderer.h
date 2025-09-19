#ifndef RENDERER_H
#define RENDERER_H

#include "../common.h"
#include <wchar.h>

typedef struct {
    wchar_t symbol;
    short fg_color;
    short bg_color;
    int attributes;
} Sprite;

void renderer_init();

void renderer_draw_sprite(WINDOW *win, int y, int x, const Sprite *sprite);

void renderer_draw_string(WINDOW *win, int y, int x, const char *text, short fg, short bg);

#endif
