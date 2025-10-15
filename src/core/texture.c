#include "core/texture.h"
#include "core/enums.h"
#include "SDL.h"
#include <assert.h>

void setpixel(texture *t, int y, int x, int rgb)
{
	int i = t->pitch/4*y + x;
	t->pixels[i] = 0xff000000|rgb;
}

void drawch(texture *t, unsigned char c, int y, int x, int color) {
	enum { COLS=32, ROWS=8 };
	static const unsigned char cp437[] = {
		#include "core/cp437.c"
	};

	if (x<0 || x>=TERM_WIDTH || y<0 || y>=TERM_HEIGHT) {
		return;
	}

	int cx = c % 32;
	int cy = c / 32;
	for (int ty = 0; ty < TERM_SCALE*FONT_HEIGHT; ty++) {
		int py = ty/TERM_SCALE;
		for (int tx = 0; tx < TERM_SCALE*FONT_WIDTH; tx++) {
			int px = tx/TERM_SCALE;
			int i = (cy*FONT_HEIGHT + py)*FONT_WIDTH*COLS +
				(cx*FONT_WIDTH  + px);
			int rgb = -!(cp437[i>>3] & (1<<(7-(i&7)))) & color;
			setpixel(
					t,
					TERM_SCALE*FONT_HEIGHT*y + ty,
					TERM_SCALE*FONT_WIDTH *x + tx,
					rgb
				);
		}
	}
}

void draws(texture *t, char *s, int len, int y, int x, int color)
{
	len = len<0 ? (int)SDL_strlen(s) : len;
	for (int i = 0; i < len; ++i) {
		drawch(t, s[i], y, x+i, color);
	}
}
