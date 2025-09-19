CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -D_DEFAULT_SOURCE

ifeq ($(shell uname), Darwin)
    LDFLAGS = -lncurses
else
    LDFLAGS = -lncursesw
endif

SOURCES = $(shell find src -name '*.c')
OBJECTS = $(SOURCES:src/%.c=obj/%.o)
EXECUTABLE = rogue_game


.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

obj/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj $(EXECUTABLE)
