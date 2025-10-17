#ifndef GAME_H
#define GAME_H

#include "global.hpp"

typedef struct {
    void (*enter)(void);
    void (*update)(void);
    void (*draw)(void);
    void (*exit)(void);
} GameState;

void game_init(void);

void game_update(void);
void game_draw(void);

void game_set_state(const GameState* newState);

#endif