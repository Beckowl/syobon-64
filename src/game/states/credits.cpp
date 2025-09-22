#include <libdragon.h>

#include "game.hpp"
#include "credits.hpp"

#include "sa_audio.hpp"
#include "sa_input.hpp"
#include "sa_graphics.hpp"

static int sTextOffset = 0;

#define TEXT_SCROLL_LIMIT -1804
#define CREDITS_LINE_COUNT 19

struct CreditsLine {
    const char* text;
    int xPos;
    int yOffset;
};

#define CENTER_LINE(length) ((SCREEN_WIDTH / 2) - length * 20 / 2)
#define CREDITS_LINE(text, length, yOffset) { text, CENTER_LINE(length), yOffset}

static CreditsLine sCredits[] = {
    CREDITS_LINE("制作・プレイに関わった方々", 13, 460),
    CREDITS_LINE("ステージ１　プレイ", 9, 540),
    CREDITS_LINE("先輩 Ｘ〜Z", 6, 590),
    CREDITS_LINE("ステージ２　プレイ", 9, 650),
    CREDITS_LINE("友人　willowlet ", 8, 700),
    CREDITS_LINE("ステージ３　プレイ", 9, 760),
    CREDITS_LINE("友人　willowlet ", 8, 810),
    CREDITS_LINE("ステージ４　プレイ", 9, 870),
    CREDITS_LINE("友人２　ann ", 6, 920),
    CREDITS_LINE("ご協力", 3, 1000),
    CREDITS_LINE("Ｔ先輩", 3, 1050),
    CREDITS_LINE("Ｓ先輩", 3, 1100),
    CREDITS_LINE("動画技術提供", 6, 1180),
    CREDITS_LINE("Ｋ先輩", 3, 1230),
    CREDITS_LINE("動画キャプチャ・編集・エンコード", 16, 1360),
    CREDITS_LINE("willowlet ", 5, 1410),
    CREDITS_LINE("プログラム・描画・ネタ・動画編集", 16, 1540),
    CREDITS_LINE("ちく", 2, 1590),
    CREDITS_LINE("プレイしていただき　ありがとうございました〜", 22, 1800),
};

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

    for (int i = 0; i < CREDITS_LINE_COUNT; i++) {
        draw_text(sCredits[i].text, sCredits[i].xPos, sTextOffset + sCredits[i].yOffset);
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