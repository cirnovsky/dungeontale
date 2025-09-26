#include "game/monster.h"
#include "game/player.h"
#include "game/map.h"

void ai_behavior_chase_player(Monster *self, Player *player) {
    int dy = player->y - self->y;
    int dx = player->x - self->x;

    int move_y = (dy > 0) - (dy < 0);
    int move_x = (dx > 0) - (dx < 0);

    int next_y = self->y + move_y;
    int next_x = self->x + move_x;

    if (map_is_walkable(next_y, next_x)) {
        self->y = next_y;
        self->x = next_x;
    }
}

void ai_behavior_move_randomly(Monster *self, Player *player) {
    int move_y = (rand() % 3) - 1; // -1, 0, or 1
    int move_x = (rand() % 3) - 1;

    int next_y = self->y + move_y;
    int next_x = self->x + move_x;

    if (map_is_walkable(next_y, next_x)) {
        self->y = next_y;
        self->x = next_x;
    }
}

void ai_behavior_stand_still(Monster *self, Player *player) {
}
