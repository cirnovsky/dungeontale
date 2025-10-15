#include "core/engine.h"
#include "core/ui.h"
#include "core/renderer.h"
#include "core/mapinit.h"
#include "core/fov.h"
#include "core/texture.h"
#include "game/hitbox.h"
#include "game/player.h"
#include "game/monster.h"
#include <unistd.h> 

extern Monster g_monsters[];
extern Hitbox g_hitboxes[];

enum {
	LVL_HEIGHT = TERM_HEIGHT-4,
	LVL_WIDTH  = TERM_WIDTH,
};

unsigned char level[LVL_HEIGHT][LVL_WIDTH] = {0};

void engine_init(Engine *engine) {
	int herox, heroy;
	ui_init();
	map_init(&herox, &heroy);
	player_init(herox, heroy);
	monsters_init();
	hitbox_init();
	fov_update(); 

	SDL_Init(SDL_INIT_VIDEO);

	engine->width  = TERM_SCALE * TERM_WIDTH  * FONT_WIDTH;
	engine->height = TERM_SCALE * TERM_HEIGHT * FONT_HEIGHT;
	engine->window = SDL_CreateWindow(
			"Dungeon Tale",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			engine
			->width, engine->height,
			0
			);
	engine->renderer = SDL_CreateRenderer(
			engine->window, -1, SDL_RENDERER_PRESENTVSYNC
			);
	engine->terminal = SDL_CreateTexture(
			engine->renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			engine->width, engine->height
			);
}

void engine_run(Engine *engine) {
	int ch;
	int game_timer = 0; 

	while (true) {
		rooms_update_visibility(g_world_map);
		game_timer++; 

		ch = ui_get_input();
		if (ch == 'a') {
			player_attack();
		}
		if (ch == 'q' || ch == KEY_ESC) {
			break;
		}
		player_set_move_target(ch); 

		ui_draw(engine);

		if (player.attack_cooldown > 0) {
			player.attack_cooldown--;
		}
		hitbox_update_all(); 
		player_update(game_timer);
		fov_update();
		monsters_update_all();

		for (int i = 0; i < MAX_HITBOXES; ++i) {
			if (!g_hitboxes[i].active) continue;

			Hitbox *hb = &g_hitboxes[i];

			for (int j = 0; j < MAX_MONSTERS; ++j) {
				if (!g_monsters[j].active) continue;

				Monster *m = &g_monsters[j];

				if (m->y >= hb->y && m->y < (hb->y + hb->height) &&
						m->x >= hb->x && m->x < (hb->x + hb->width)) 
				{
					ui_log_message("Ouch!");
					monster_die(m);
				}
			}
		}

		SDL_Delay(30); // 30ms delay (equivalent to usleep(30000))
	}
}

void handle_resize(){
	/*
	   ui_recreate_windos();
	   clear();
	   refresh();
	   ui_draw();
	   */
}

void engine_shutdown() {
	//map_destroy(g_world_map);
	ui_shutdown();
}
