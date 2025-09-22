#include <libdragon.h>

#include "global.hpp"
#include "transition.hpp"

#include "sa_graphics.hpp"

static int sTransitionTimer = 0;
static int sTransitionDuration = 30;
static bool sDeathTransition = false;

void transition_enter(void) {
    sTransitionTimer = 0;
}

void transition_update(void) {
    sTransitionTimer++;
    
    // it seems fast will always be 0 during gameplay?? not sure though
	if (fast == 1) {
	    sTransitionTimer += 2;
    }

	if (sTransitionTimer >= sTransitionDuration) {
	   game_set_state(STATE_PLAY);
	}
}

void transition_draw(void) {
    rdpq_clear(RGBA32(0, 0, 0, 0));
	
	if (sDeathTransition) {
		draw_sprite(grap[0][0], RECENTER_X(190), 190);

		char buf[16];
		snprintf(buf, sizeof(buf), " × %d", nokori);

		draw_text(buf, RECENTER_X(230), 218);
	}
}

GameState STATE_TRANSITION = {
    .enter = transition_enter,
    .update = transition_update,
    .draw = transition_draw,
};

void play_transition(int duration, bool deathTransition) {
	sTransitionDuration = duration;
	sDeathTransition = deathTransition;
	
    game_set_state(STATE_TRANSITION);
}

