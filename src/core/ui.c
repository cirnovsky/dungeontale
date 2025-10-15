#include "core/ui.h"
#include "core/texture.h"
#include "core/mapinit.h"
#include "core/enums.h"
#include "game/player.h"
#include "game/hitbox.h"
#include "game/monster.h"
#include "game/monster.h"
#include "game/map.h"
#include "common.h"
#include "SDL.h"
#include <stdarg.h>
#include <stdio.h>
#include <assert.h>

WindowArea *mynewwin(int x, int y, int h, int w) {
	WindowArea *win = malloc(sizeof(WindowArea));
	win->x = x;
	win->y = y;
	win->h = h;
	win->w = w;
	return win;
}

WindowArea *win_main;
WindowArea *win_log;
WindowArea *win_inv; // inventory

void ui_init() {
	win_main = mynewwin(0, 0, TERM_HEIGHT*4/5, TERM_WIDTH);
	win_log = mynewwin(TERM_HEIGHT*4/5, 0, TERM_HEIGHT - TERM_HEIGHT*4/5 - 2, TERM_WIDTH);
	win_inv = mynewwin(TERM_HEIGHT-2, 0, 2, TERM_WIDTH);
}

void ui_shutdown() {}
enum {
	LVL_HEIGHT = TERM_HEIGHT-4,
	LVL_WIDTH  = TERM_WIDTH,
}; // TODO delete

void map_draw(texture *t, int x, int y)
{
	int h = win_main->h, w = win_main->w;
	for (int i = x; i < x+h; ++i) {
		for (int j = y; j < y+w; ++j) {
			unsigned char ch = TILE_EMPTY;
			int fg = 0x000000;
			if (0 <= i && i < MAP_HEIGHT && 0 <= j && j < MAP_WIDTH) {
				ch = map_layout[i][j];
				fg = mapfg[i][j];
			}
			drawch(t, ch, i-x+1, j-y+1, fg);
		}
	}
}

void inv_draw(texture *t) {
	int x = TERM_HEIGHT-1, y = TERM_WIDTH/2 - 20;

	draws(t, "HP: 100/100    GOLD:  3/80    MANA:    1/9", -1, x, y, 0xff00ff);
}

char *logmsg;

void ui_draw(Engine *engine) {
	void *pixels;
	texture t[1] = {0};
	SDL_LockTexture(engine
			->terminal, 0, &pixels, &t->pitch);
	t->pixels = SDL_memset(pixels, 0, engine->height*t->pitch);

	static int x = 0, y = 0;
	int px = player.y, py = player.x;
	int h = win_main->h, w = win_main->w;

	if (x - px < h / 10 || x - px > h * 9 / 10) {
		x = px - h / 2;
	}
	if (y - py < w / 10 || y - py > w * 9 / 10) {
		y = py - w / 2;
	}

	map_draw(t, x, y);
	inv_draw(t);
	draws(t, logmsg, -1, 0, 0, 0xffffff);
	hitbox_draw_all(win_main, t, x, y);
	monsters_draw_all(win_main, t, x, y);
	player_draw(win_main, t, x, y);

	SDL_UnlockTexture(engine->terminal);
	SDL_RenderCopy(engine->renderer, engine->terminal, 0, 0);
	SDL_RenderPresent(engine->renderer);
}
void ui_recreate_windos() {}
void ui_log_message(const char *format, ...) {
	static char formatted_message[512];
	va_list args;

	va_start(args, format);
	vsnprintf(formatted_message, sizeof(formatted_message), format, args);
	va_end(args);

	// For now, just print to console - in a full implementation,
	// you'd want to maintain a log buffer and display it in the log window
	logmsg = formatted_message;
}
int ui_get_input() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				return KEY_ESC;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDL_QUIT:
						return KEY_ESC;
					case SDLK_UP:
						return KEY_UP;
					case SDLK_DOWN:
						return KEY_DOWN;
					case SDLK_LEFT:
						return KEY_LEFT;
					case SDLK_RIGHT:
						return KEY_RIGHT;
					case SDLK_ESCAPE:
						return KEY_ESC;
					case SDLK_q:
						return 'q';
					case SDLK_w:
						return 'w';
					case SDLK_a:
						return 'a';
					case SDLK_s:
						return 's';
					case SDLK_d:
						return 'd';
					case SDLK_SPACE:
						return ' ';
					default:
						return event.key.keysym.sym;
				}
				break;
		}
	}
	return 0; // No input
}
