
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Ilib -D_DEFAULT_SOURCE -D_XOPEN_SOURCE_EXTENDED -g

ifeq ($(shell uname), Darwin)
    LDFLAGS = -lncurses -lm
else
    LDFLAGS = -lncursesw -lm
endif

# All sources except test.c and main.c
SOURCES = $(shell find src -name '*.c' ! -name 'test.c')
OBJECTS = $(SOURCES:src/%.c=obj/%.o)

EXECUTABLE = dungeontale
TEST_EXECUTABLE = test

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
