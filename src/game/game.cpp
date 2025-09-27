#include <libdragon.h>

#include "game.hpp"
#include "loadg.hpp"
#include "sa_audio.hpp"

#include "states/title_screen.hpp"

static GameState sCurrState = STATE_TITLE_SCREEN;

#define CALL_STATE_FUNC(func) if (sCurrState.func) { sCurrState.func(); }

void game_init(void) {
    loadg();
}

void game_update(void) {
    CALL_STATE_FUNC(update);
}
void game_draw(void) {
    CALL_STATE_FUNC(draw);
}

void game_set_state(GameState newState) {
    CALL_STATE_FUNC(exit);

    sCurrState = newState;

    CALL_STATE_FUNC(enter);
}
