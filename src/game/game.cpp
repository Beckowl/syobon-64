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

void game_deinit(void) {
    for (int t = 0; t < 51; t++) {
		sprite_t* sprite = mgrap[t];
		if (sprite != NULL) {
			sprite_free(mgrap[t]); 	// TODO: rename SpriteInfo functions, this is messy
		}
	}

    for (int i = 0; i < 161; i++) {
		for (int j = 0; j < 8; j++) {
	    	free(grap[i][j]); // lmao
		}
	}
	
    for (int i = 1; i < 6; i++) {
	    free_sound(otom[i]);
    }

    for (int i = 1; i < 19; i++) {
	    free_sound(oto[i]);
    }
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
