CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -Ilib
LDFLAGS = -lncurses

SRC_FILES = $(wildcard src/**/*.c src/*.c)
OBJ_FILES = $(patsubst src/%.c, obj/%.o, $(SRC_FILES))
EXECUTABLE = dungeontale

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(EXECUTABLE) $(LDFLAGS)

obj/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj $(EXECUTABLE)
