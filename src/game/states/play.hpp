#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "game.hpp"

#define rand(x) rand() % x

void tekizimen();
void stagecls();
void stage();
void stagep();
void tyobi(int x, int y, int type);
void brockbreak(int t);
void spawn_particle(int xa, int xb, int xc, int xd, int xe, int xf, int xnobia, int xnobib, int xgtype, int xtm);
void spawn_enemy(int xa, int xb, int xc, int xd, int xnotm, int xtype, int xxtype);
void player_init_checkpoint(void);
void spawn_decoration(int type, int x, int y);
void set_enemy_spawn(int type, int subtype, int x, int y);
void spawn_platform(int type, int subtype, int fallSpeed, int x, int y, int width);
void spawn_general_object(int type, int subtype, int x, int y, int width, int height);

extern const GameState STATE_PLAY;

#endif