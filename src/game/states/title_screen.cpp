#include <libdragon.h>

#include "global.hpp"
#include "title_screen.hpp"
#include "transition.hpp"

#include "sa_audio.hpp"
#include "sa_graphics.hpp"
#include "sa_input.hpp"
#include "controls.hpp"

#define STAGE_MAX 10 // 1-9 + mystery dungeon (randomized map)
#define STAGE_MIN 1
#define STAGE_MYSTERY_DUNGEON 10

static uint8_t sStageNum = 1;
static bool sShowStageNum = false;

static void handle_scrolling(void) {
    bool lPressed = is_button_pressed(CONTROL_PAGE_DOWN);
    bool rPressed = is_button_pressed(CONTROL_PAGE_UP);

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

static void select_stage(uint8_t num) {
    if (num >= STAGE_MYSTERY_DUNGEON) {
        num = STAGE_MIN;
    }

    sta = (num - 1) / 4 + 1; // current world?
    stb = (num - 1) % 4 + 1; // current level??
    stc = 0;
}

static void enter_stage() {
	zxon = 0;
	maintm = 0;
	nokori = 2;

	fast = 0;
	trap = 0;
	tyuukan = 0;

    over = sStageNum == STAGE_MYSTERY_DUNGEON;

    play_transition(30, true);
}

void title_screen_enter(void) {
    sStageNum = STAGE_MIN;
    sShowStageNum = false;

    stop_background_music();
}

void title_screen_update(void) {
    handle_scrolling();

	if (is_button_down(CONTROL_START_PAUSE)) {
        select_stage(sStageNum);
	    enter_stage();
	}
}

void title_screen_draw(void) {
    rdpq_clear(RGBA32(160, 180, 250, 255));

    // syobon action logo
    rdpq_set_mode_standard();
    rdpq_sprite_blit(mgrap[30], RECENTER_X(50), 60, NULL);

    // decor
    draw_sprite_region(grap[0][4], 360, 278);
    draw_sprite_region(grap[1][4], 180, 336);
    draw_sprite_region(grap[0][0], 60, 330); // this is syobon!!

    // floor
    for (t = 0; t <= 19; t++) {
        draw_sprite_region(grap[5][1], 29 * t, 365);
        draw_sprite_region(grap[6][1], 29 * t, 394);
    }

    if (!gControllerFound) {
        draw_text("No controller!", RECENTER_X(160), 250);
        return;
    }

    // TODO: use paragraphs so text can be centered regardless of width
    draw_text("STARTボタンを押せ!!", RECENTER_X(160), 250);

    if (sShowStageNum) {
        if (sStageNum != STAGE_MYSTERY_DUNGEON) {
            draw_text_fmt(RECENTER_X(160), 270, "Stage number: %d", sStageNum);
        } else {
            draw_text("Mystery Dungeon", RECENTER_X(160), 270);
        }
    }
}

GameState STATE_TITLE_SCREEN = {
    .enter = title_screen_enter,
    .update = title_screen_update,
    .draw = title_screen_draw,
};
