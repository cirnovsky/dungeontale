#include "game/hitbox.h"
#include "game/map.h"
#include "core/renderer.h"
#include "core/ui.h"
#include <stdio.h>

#define MAX_HITBOXES 10

static Hitbox g_hitboxes[MAX_HITBOXES];

void hitbox_init() {
    for (int i = 0; i < MAX_HITBOXES; ++i) {
        g_hitboxes[i].active = false;
    }
}

void hitbox_create(int y, int x, int h, int w, int lifetime){
    for (int i = 0; i < MAX_HITBOXES; ++i){
        if(!g_hitboxes[i].active){
            g_hitboxes[i].y = y;
            g_hitboxes[i].x = x; 
            g_hitboxes[i].height = h;
            g_hitboxes[i].width = w;
            g_hitboxes[i].lifetime = lifetime;
            g_hitboxes[i].active = true;
            break;
        }
    }
}

void hitbox_update_all() {
    for (int i = 0; i < MAX_HITBOXES; ++i) {
        if (!g_hitboxes[i].active) {
            continue; 
        }

        g_hitboxes[i].lifetime--;

        if (g_hitboxes[i].lifetime < 0) { 
            g_hitboxes[i].active = false;
        }
    }
}

void hitbox_draw_all(WINDOW *win){
    Sprite hitbox_sprite = {
        .symbol = L'*',
        .fg_color = COLOR_RED,
        .bg_color = -1,
        .attributes = A_NORMAL
   };

   bool found_active_hitbox = false;

   for (int i = 0; i < MAX_HITBOXES; ++i){
       if (g_hitboxes[i].active){
            
            found_active_hitbox = true;

            Hitbox *hb = &g_hitboxes[i];

            char debug_msg[128];
            sprintf(debug_msg, "Frame: Drawing active hitbox #%d: lifetime=%d, y=%d, x=%d", 
                             0, i, hb->lifetime, hb->y, hb->x);
            ui_log_message(debug_msg);


            for (int j = 0; j < hb->height; ++j){
                for (int k = 0; k < hb->width; ++k){
                    int world_y = hb->y + j;
                    int world_x = hb->x +k;

                    if (map_is_walkable(world_y, world_x)){
                        renderer_draw_sprite(win, world_y + 1, world_x + 1, &hitbox_sprite);
                    }
                }

            }
       }
   }
   if (!found_active_hitbox) {
    //    ui_log_message("Frame: No active hitboxes to draw."); // 你可以取消这行的注释来获得更详细的信息
    }
}


