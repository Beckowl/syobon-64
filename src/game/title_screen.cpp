#include <libdragon.h>

#include "title_screen.hpp"
#include "game.hpp"

#include "sa_audio.hpp"
#include "sa_graphics.hpp"
#include "sa_input.hpp"
#include "controls.hpp"

#define STAGE_MAX 10 // 1-9 + mystery dungeon (randomized map)
#define STAGE_MIN 1
#define STAGE_MYSTERY_DUNGEON 10

static byte sStageNum = 1;
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

static void select_stage(byte num) {
    sta = (num - 1) / 4 + 1; // current world?
    stb = (num - 1) % 4 + 1; // current level??
    stc = 0;
}

void title_screen_enter(void) {
    sStageNum = STAGE_MIN;
    sShowStageNum = false;

    mainZ = 100;

    stop_background_music();
}

void title_screen_exit(void) {
    select_stage(sStageNum);
	
    mainZ = 10;
	zxon = 0;
	maintm = 0;
	nokori = 2;

	fast = 0;
	trap = 0;
	tyuukan = 0;

    over = sStageNum == STAGE_MYSTERY_DUNGEON;
}

void title_screen_update(void) {
	xx[0] = 0;

    handle_scrolling();

	if (CheckHitKey(CONTROL_START_PAUSE) == 1) {
        title_screen_exit();
	}
}

void title_screen_draw(void) {
    rdpq_clear(RGBA32(160, 180, 250, 255));

    // syobon action logo
    rdpq_set_mode_standard();
    rdpq_sprite_blit(mgrap[30], RECENTER_X(50), 60, NULL);

    // decor
    draw_sprite(grap[0][4], 360, 278);
    draw_sprite(grap[1][4], 180, 336);
    draw_sprite(grap[0][0], 60, 330); // this is syobon!!

    // floor
    for (t = 0; t <= 19; t++) {
        draw_sprite(grap[5][1], 29 * t, 365);
        draw_sprite(grap[6][1], 29 * t, 394);
    }

    if (!gControllerFound) {
        draw_text("No controller!", RECENTER_X(160), 250);
        return;
    }

    draw_text("Enterキーを押せ!!", RECENTER_X(160), 250);

    static char buf[32];

    if (sShowStageNum) {
        if (sStageNum != STAGE_MYSTERY_DUNGEON) {
            sprintf(buf, "Stage number: %d", sStageNum);
            draw_text(buf, RECENTER_X(160), 270);
        } else {
            draw_text("Mystery Dungeon", RECENTER_X(160), 270);
        }
    }
}
