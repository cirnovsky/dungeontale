#ifndef MONSTER_AI_H
#define MONSTER_AI_H

struct Monster;
struct Player;

void ai_behavior_chase_player(Monster *self, struct Player *player);
void ai_behavior_move_randomly(Monster *self, struct Player *player);
void ai_behavior_stand_still(Monster *self, struct Player *player);

#endif
