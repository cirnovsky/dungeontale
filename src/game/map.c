#include "game/map.h"
#include "core/ui.h"

#define MAP_HEIGHT 20
#define MAP_WIDTH 60

static const char *map_layout[MAP_HEIGHT] = {
    "############################################################",
    "#                                                          #",
    "#                                                          #",
    "#     ####                                                 #",
    "#    ##  ##        #######                                 #",
    "#   ##    ##                                               #",
    "#  ##      ##                                              #",
    "#                                                          #",
    "#                                                          #",
    "#                  ##########                              #",
    "#                                                          #",
    "#         ####                                             #",
    "#        ##  ##                                            #",
    "#       ##    ##                                           #",
    "#                                                          #",
    "#               ############                               #",
    "#                                                          #",
    "#                                                          #",
    "#                                                          #",
    "############################################################"

};

void map_draw(){
    for (int y = 0; y < MAP_HEIGHT; ++y){
        mvwprintw(win_main, y+1, 1, "%s", map_layout[y]);    
    }
}

bool map_is_walkable(int y, int x){
    if (y < 0 || y >= MAP_HEIGHT || x < 0 || x >= MAP_WIDTH){
        return false;
    }
    return map_layout[y][x] != '#';
}
