#ifndef TRANSITION_STATE_H
#define TRANSITION_STATE_H

#include "game.hpp"

extern const GameState STATE_TRANSITION;

void play_transition(const GameState* nextState, uint16_t duration, bool showLives);

#endif