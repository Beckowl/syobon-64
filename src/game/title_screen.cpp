#include <libdragon.h>

#include "title_screen.h"
#include "game.h"
#include "sa_graphics.h"
#include "sa_input.h"
#include "controls.h"

#define STAGE_MAX 10 // 1-9 + mystery dungeon (randomized map)
#define STAGE_MIN 1
#define STAGE_MYSTERY_DUNGEON 10

static byte sStageNum = 1;
static bool sShowStageNum = false;
static bool sInitialized = false;

static void title_screen_init(void) {
    sStageNum = STAGE_MIN;
    sShowStageNum = false;
    sInitialized = true;
}

static void handle_scrolling(void) {
    bool lPressed = is_button_pressed(BUTTON_PAGE_DOWN);
    bool rPressed = is_button_pressed(BUTTON_PAGE_UP);

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
    sta = (num - 1) / 4 + 1;
    stb = (num - 1) % 4 + 1;
    stc = 0;
}

static void enter_stage() {
    xx[0] = 1;

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

    if (!sInitialized) {
        title_screen_init();
    }

    handle_scrolling();

	if (CheckHitKey(BUTTON_START_PAUSE) == 1) {
        select_stage(sStageNum);
	    enter_stage();
        sInitialized = false;
	}
}

void title_screen_draw(void) {
    rdpq_clear(RGBA32(160, 180, 250, 255));

    // syobon action logo
    rdpq_set_mode_standard();
    rdpq_mode_alphacompare(1);
    rdpq_sprite_blit(mgrap[30], 50, 60, NULL);

    // decor
    draw_sprite(grap[0][4], 360, 278, false);
    draw_sprite(grap[1][4], 180, 336, false);
    draw_sprite(grap[0][0], 60, 330, false); // this is syobon!!

    // floor
    for (t = 0; t <= 16; t++) {
        draw_sprite(grap[5][1], 29 * t, 365, false);
        draw_sprite(grap[6][1], 29 * t, 394, false);
    }

    if (gControllerFound) {
        draw_text("Enterキーを押せ!!", 160, 250);
    } else {
        draw_text("No controller!", 160, 250);
    }

    static char buf[32];

    if (sShowStageNum) {
        if (sStageNum != STAGE_MYSTERY_DUNGEON) {
            sprintf(buf, "Stage number: %d", sStageNum);
            draw_text(buf, 160, 270);
        } else {
            draw_text("Mystery Dungeon", 160, 270);
        }
    }
}
