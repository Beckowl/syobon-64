#include <libdragon.h>

#include "global.hpp"
#include "title_screen.hpp"
#include "transition.hpp"
#include "states/play.hpp"

#include "sa_audio.hpp"
#include "sa_graphics.hpp"
#include "sa_input.hpp"

#define STAGE_MAX 10 // 1-9 + mystery dungeon (randomized map)
#define STAGE_MIN 1
#define STAGE_MYSTERY_DUNGEON 10

static uint8_t sStageNum = 1;
static bool sShowStageNum = false;

static void handle_scrolling(void) {
    bool lPressed = is_button_pressed(BUTTON_L);
    bool rPressed = is_button_pressed(BUTTON_R);

    if (lPressed || rPressed) {
        if (!sShowStageNum) {
            sShowStageNum = true;
            return; // do not change stageNum the first time L/R is pressed
        }

        if (lPressed && sStageNum > STAGE_MIN) {
            sStageNum--;
        }
        if (rPressed && sStageNum < STAGE_MAX) {
            sStageNum++;
        }
    }
}

static void enter_stage() {
    nokori = 2;
	fast = 0;
	trap = 0;
	tyuukan = 0;
    over = sStageNum == STAGE_MYSTERY_DUNGEON;

    if (sStageNum >= STAGE_MYSTERY_DUNGEON) {
        sStageNum = STAGE_MIN;
    }

    sta = (sStageNum - 1) / 4 + 1;  // current world
    stb = (sStageNum - 1) % 4 + 1;  // current level
    stc = 0;                        // current area

    play_transition(&STATE_PLAY, 30, true);
}

static void title_screen_enter(void) {
    sStageNum = STAGE_MIN;
    sShowStageNum = false;

    stop_background_music();
}

static void title_screen_update(void) {
    handle_scrolling();

	if (is_button_pressed(BUTTON_START | BUTTON_A)) {
	    enter_stage();
	}
}

static void title_screen_draw(void) {
    rdpq_clear(RGBA32(160, 180, 250, 255));

    // syobon action logo
    rdpq_set_mode_standard();
    rdpq_sprite_blit(mgrap[30], RECENTER_X(50), 60, NULL);

    // decor
    draw_sprite_region(grap[0][4], RESCALE_X(360), 278);
    draw_sprite_region(grap[1][4], RESCALE_X(180), 336);
    draw_sprite_region(grap[0][0], RESCALE_X(60), 330); // this is syobon!!

    // floor
    const int FLOOR_WIDTH = SCREEN_WIDTH / 29;

    for (int t = 0; t <= FLOOR_WIDTH; t++) {
        draw_sprite_region(grap[5][1], t * 29, 365);
        draw_sprite_region(grap[6][1], t * 29, 394);
    }

    uint16_t textWidth = 0;
    int16_t textX = 0;

    if (!gControllerFound) {
        const char* text = "NO CONTROLLER!";

        measure_text(text, &textWidth, NULL);
        textX = (SCREEN_WIDTH - textWidth) / 2;

        draw_text(text, textX, 250);
        return;
    }

    const char* text = "STARTボタンを押せ!!";

    measure_text(text, &textWidth, NULL);
    textX = (SCREEN_WIDTH - textWidth) / 2;

    draw_text(text, textX, 250);

    if (sShowStageNum) {
        if (sStageNum != STAGE_MYSTERY_DUNGEON) {
            draw_text_fmt(textX, 270, "Stage number: %d", sStageNum);
        } else {
            draw_text("Mystery Dungeon", textX, 270);
        }
    }
}

const GameState STATE_TITLE_SCREEN = {
    .enter = title_screen_enter,
    .update = title_screen_update,
    .draw = title_screen_draw,
};
