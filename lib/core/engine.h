#ifndef ENGINE_H
#define ENGINE_H

#include "../common.h"
#include "core/enums.h"

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *terminal;
	int width, height;
	unsigned char level[MAP_HEIGHT][MAP_WIDTH];
} Engine;

void engine_init(Engine *engine);
void engine_run(Engine *engine);
void engine_shutdown();
void handle_resize();

#endif
