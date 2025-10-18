CC = gcc
# Use pkg-config for SDL2 include paths, keep your own -Ilib
CFLAGS = -Wall -Wextra -std=c99 -Ilib -D_DEFAULT_SOURCE -g $(shell pkg-config --cflags sdl2 SDL2_image SDL2_ttf SDL2_mixer)

# --- Platform Detection ---
OS := $(shell uname -s)
EXECUTABLE = dungeontale
TEST_EXECUTABLE = test

# Default LDFLAGS for Linux (ncursesw)
LDFLAGS = -lncursesw -lm $(shell pkg-config --libs sdl2 SDL2_image SDL2_ttf SDL2_mixer)

# macOS specific LDFLAGS (ncurses)
ifeq ($(OS), Darwin)
    LDFLAGS = -lncurses -lm $(shell pkg-config --libs sdl2 SDL2_image SDL2_ttf SDL2_mixer)
endif

# Windows (MSYS2/MinGW) specific LDFLAGS (ncurses) and executable name
# Check if uname output contains MINGW or MSYS
ifneq (,$(findstring MINGW,$(OS))) # Check for MINGW first
    LDFLAGS = -lncurses -lm $(shell pkg-config --libs sdl2 SDL2_image SDL2_ttf SDL2_mixer) -mwindows
    EXECUTABLE = dungeontale.exe
    TEST_EXECUTABLE = test.exe
else ifneq (,$(findstring MSYS,$(OS))) # Check for MSYS as fallback
    LDFLAGS = -lncurses -lm $(shell pkg-config --libs sdl2 SDL2_image SDL2_ttf SDL2_mixer) -mwindows
    EXECUTABLE = dungeontale.exe
    TEST_EXECUTABLE = test.exe
endif
# --- End Platform Detection ---


# All sources except test.c and main.c
SOURCES = $(shell find src -name '*.c' ! -name 'test.c')
OBJECTS = $(SOURCES:src/%.c=obj/%.o)

.PHONY: all clean test

all: $(EXECUTABLE)

# Build main game
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

obj/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# ---- TEST BUILD ----
# Exclude main.o so only test.c has a main()
TEST_OBJECTS = $(filter-out obj/main.o, $(OBJECTS))

test: src/test.c $(TEST_OBJECTS)
	$(CC) $(CFLAGS) src/test.c $(TEST_OBJECTS) -o $(TEST_EXECUTABLE) $(LDFLAGS)
	./$(TEST_EXECUTABLE)

clean:
	rm -rf obj $(EXECUTABLE) $(TEST_EXECUTABLE)
