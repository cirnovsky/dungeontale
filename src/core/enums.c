#include "core/enums.h"
#include <stdlib.h>

//const wchar_t *LEGENDS = L" #.\u2588\u2551\u2550\u2554\u2557\u255a\u255d\u233b";

const wchar_t LEGENDS[] = {
    [TILE_EMPTY]      = L' ',
    [TILE_ROOM]       = L'·',
    [TILE_CORRIDOR]   = L'\u2588',
    [TILE_PORT]       = L'\u233b',
    [TILE_WALL]       = L'#',
    [TILE_WALL_HOR]   = L'\u2551',
    [TILE_WALL_VER]   = L'\u2550',
    [TILE_WALL_COR_LU]  = L'\u2554',
    [TILE_WALL_COR_RU]  = L'\u2557',
    [TILE_WALL_COR_LD]  = L'\u255a',
    [TILE_WALL_COR_RD]  = L'\u255d'
};
