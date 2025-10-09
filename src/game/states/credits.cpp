#include <libdragon.h>

#include "credits_text.hpp"

#include "game.hpp"
#include "credits.hpp"
#include "title_screen.hpp"

#include "sa_audio.hpp"
#include "sa_input.hpp"
#include "sa_graphics.hpp"

static int sTextOffset = 0;

#define TEXT_SCROLL_LIMIT -1804

static void credits_enter(void)
{
    set_background_music(otom[5]);
    sTextOffset = 0;
}

void credits_update(void) {
    if (is_button_down(BUTTON_B)) {
        sTextOffset -= 3;
    }

    sTextOffset--;

	if (sTextOffset <= TEXT_SCROLL_LIMIT) {
	   game_set_state(STATE_TITLE_SCREEN);
	}
}

void credits_draw(void) {
    rdpq_clear(RGBA32(0, 0, 0, 0));

    for (uint32_t i = 0; i < CREDITS_LINE_COUNT; i++) {
        draw_text(gCreditsText[i].text, gCreditsText[i].xPos, sTextOffset + gCreditsText[i].yOffset);
    }
}

static void credits_exit(void) {
	stop_background_music();
}

GameState STATE_CREDITS = {
    .enter = credits_enter,
    .update = credits_update,
    .draw = credits_draw,
    .exit = credits_exit,
};