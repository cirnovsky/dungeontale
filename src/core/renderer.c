#include <ncurses.h>
#include "core/renderer.h"
#include <string.h>
#include <wchar.h>
#define MAX_COLOR_PAIRS 256

static struct {
    short fg;
    short bg;
} color_pair_map[MAX_COLOR_PAIRS];

static int num_color_pairs = 1;

short get_or_create_color_pair(short fg, short bg){
    for (int i = 1; i < num_color_pairs; ++i){
        if (color_pair_map[i].fg == fg && color_pair_map[i].bg == bg){
            return i;
        }    
    }   
    if (num_color_pairs < MAX_COLOR_PAIRS){
        init_pair(num_color_pairs, fg, bg);
        color_pair_map[num_color_pairs].fg = fg; 
        color_pair_map[num_color_pairs].bg = bg;
        return num_color_pairs++;
        
    }

    return 1;
}
void renderer_init(){
    if (has_colors()){
        start_color();        

        use_default_colors();
    }
}

void renderer_draw_sprite(WINDOW *win, int y, int x, const Sprite *sprite){
    short pair_id = get_or_create_color_pair(sprite->fg_color, sprite->bg_color);

    wchar_t wch_string[2];
    wch_string[0] = sprite->symbol;
    wch_string[1] = L'\0'; 

    cchar_t wc;
    setcchar(&wc, wch_string, sprite->attributes, pair_id, NULL);

    wattron(win, COLOR_PAIR(pair_id) | sprite->attributes);
    mvwadd_wch(win, y, x, &wc);
    wattroff(win, COLOR_PAIR(pair_id) | sprite->attributes);

}

