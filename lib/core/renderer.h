#ifndef RENDERER_H
#define RENDERER_H

#include "../common.h"
#include "core/ui.h"
#include "core/texture.h"

typedef struct {
    unsigned char symbol;
    short fg_color;
    short bg_color;
    int attributes;
} Sprite;

void renderer_init();

void renderer_draw_sprite(WindowArea *win, texture *t, int y, int x, const Sprite *sprite);

void renderer_draw_string(WindowArea *win, texture *t, int y, int x, const char *text, short fg, short bg);

#endif
