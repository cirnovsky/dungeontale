#include "core/enums.h"
#include <stdlib.h>

//const wchar_t *LEGENDS = L" #.\u2588\u2551\u2550\u2554\u2557\u255a\u255d\u233b";

// https://en.wikipedia.org/wiki/Code_page_437

const unsigned char LEGENDS[] = {
    [TILE_EMPTY]      = 0,
    [TILE_ROOM]       = '.',
    [TILE_CORRIDOR]   = 0xb2,
    [TILE_PORT]       = 0xce,
    [TILE_WALL]       = 0,
    [TILE_WALL_HOR]   = 0xba,
    [TILE_WALL_VER]   = 0xcd,
    [TILE_WALL_COR_LU]  = 0xc9,
    [TILE_WALL_COR_RU]  = 0xbb,
    [TILE_WALL_COR_LD]  = 0xc8,
    [TILE_WALL_COR_RD]  = 0xbc
};
