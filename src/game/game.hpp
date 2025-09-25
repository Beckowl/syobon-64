#ifndef GAME_H
#define GAME_H

#include "global.hpp"
#include "controls.hpp"

typedef struct {
    void (*enter)(void);
    void (*update)(void);
    void (*draw)(void);
    void (*exit)(void);
} GameState;

void game_init(void);
void game_deinit(void);

void game_update(void);
void game_draw(void);

void game_set_state(GameState newState);

#endif