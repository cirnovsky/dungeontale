#ifndef COMMON_H
#define COMMON_H

#include "SDL.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Color definitions (matching ncurses colors)
#define COLOR_BLACK   0
#define COLOR_RED     1
#define COLOR_GREEN   2
#define COLOR_YELLOW  4
#define COLOR_BLUE    3
#define COLOR_MAGENTA 6
#define COLOR_CYAN    5
#define COLOR_WHITE   7

// Text attributes (matching ncurses)
#define A_NORMAL    0
#define A_BOLD      1
#define A_DIM       2
#define A_UNDERLINE 4
#define A_BLINK     8
#define A_REVERSE   16

// Key codes (matching ncurses)
#define KEY_UP      1
#define KEY_DOWN    2
#define KEY_LEFT    3
#define KEY_RIGHT   4
#define KEY_ESC     27

#endif
