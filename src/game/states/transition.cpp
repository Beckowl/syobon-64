#include <libdragon.h>

#include "game.hpp"
#include "transition.hpp"
#include "play.hpp"

#include "sa_graphics.hpp"

static const GameState* sNextState = NULL;
static int sTransitionTimer = 0;
static int sTransitionDuration = 30;
static bool sShowLives = false;

void transition_enter(void) {
    sTransitionTimer = 0;
}

void transition_update(void) {
    sTransitionTimer++;
    
	if (fast == 1) {
	    sTransitionTimer += 2;
    }

	if (sTransitionTimer >= sTransitionDuration) {
	   game_set_state(sNextState);
	}
}

void transition_draw(void) {
    rdpq_clear(RGBA32(0, 0, 0, 0));
	
	if (sShowLives) {
		draw_sprite_region(grap[0][0], RECENTER_X(190), 190);

        draw_text_fmt(RECENTER_X(230), 200, " × %d", nokori);
	}
}

void play_transition(const GameState* nextState, uint16_t duration, bool showLives) {
    sNextState = nextState;
	sTransitionDuration = duration;
	sShowLives = showLives;
	
    game_set_state(&STATE_TRANSITION);
}

const GameState STATE_TRANSITION = {
    .enter = transition_enter,
    .update = transition_update,
    .draw = transition_draw,
};
