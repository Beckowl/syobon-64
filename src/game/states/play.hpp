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
void eyobi(int xa, int xb, int xc, int xd, int xe, int xf, int xnobia, int xnobib, int xgtype, int xtm);
void ayobi(int xa, int xb, int xc, int xd, int xnotm, int xtype, int xxtype);
void spawn_decoration(int type, int x, int y);
void set_enemy_spawn(int type, int subtype, int x, int y);

extern GameState STATE_PLAY;

#endif