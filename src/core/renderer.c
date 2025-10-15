#include "core/renderer.h"
#include "core/texture.h"
#define MAX_COLOR_PAIRS 256

int make_rgb(short fg, short bg)
{
	(void)bg;
	switch (fg) {
		case 1: return 0xff0000; // red
		case 2: return 0x00ff00; // green
		case 3: return 0x0000ff; // blue
		case 4: return 0xffff00; // yellow
		case 5: return 0x00ffff; // cyan
		case 6: return 0xff00ff; // magenta
		case 7: return 0xffffff; // white
		default: return 0xaaaaaa; // gray
	}
}

void renderer_draw_sprite(WindowArea *win, texture *t, int y, int x, const Sprite *sprite)
{
	unsigned char ch = sprite->symbol;
	int color = make_rgb(sprite->fg_color, sprite->bg_color);

	drawch(t, ch, y, x, color);
}

void renderer_draw_string(WindowArea *win, texture *t, int y, int x, const char *text, short fg, short bg)
{
}
