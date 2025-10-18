#include <libdragon.h>

#include "global.hpp"
#include "message_box.hpp"
#include "message_text.hpp"

#include "sa_graphics.hpp"
#include "sa_input.hpp"
#include "sa_audio.hpp"

typedef enum {
    STATE_NONE,
    STATE_OPEN,
    STATE_SHOW,
    STATE_CLOSE,
} MessageBoxState;

MessageBoxState sCurrentState = STATE_NONE;
TextMessageId sCurrentMessage = MESSAGE_NONE;

static bool sMessageBoxActive = false;

int sScrollTop = 0;
int sScrollBottom = 0;

#define MESSAGE_BOX_Y 40
#define MESSAGE_BOX_X RECENTER_X(60)
#define MESSAGE_BOX_WIDTH 360
#define MESSAGE_BOX_HEIGHT 183
#define PADDING 6
#define SCROLL_SPEED 12

#define IS_VALID_MESSAGE(id) (id >= MESSAGE_000 && id <= MESSAGE_MAX)

void message_box_open(TextMessageId messageId) {
    if (IS_VALID_MESSAGE(messageId)) {
        sMessageBoxActive = true;
        sCurrentMessage = messageId;
        sCurrentState = STATE_OPEN;

        sScrollTop = MESSAGE_BOX_Y;
        sScrollBottom = MESSAGE_BOX_Y;

        play_sound_effect(oto[15]);
    }
}

void message_box_reset(void) {
    sCurrentMessage = MESSAGE_NONE;
    sCurrentState = STATE_NONE;
    sScrollTop = MESSAGE_BOX_Y;
    sScrollBottom = MESSAGE_BOX_Y;
    sMessageBoxActive = false;
}

static void message_box_open_update(void) {
    sScrollBottom += SCROLL_SPEED;
    if (sScrollBottom >= MESSAGE_BOX_Y + MESSAGE_BOX_HEIGHT) {
        sScrollBottom = MESSAGE_BOX_Y + MESSAGE_BOX_HEIGHT;
        sCurrentState = STATE_SHOW;
    }
}

static void message_box_show_update(void) {
    joypad_buttons_t pressed = joypad_get_buttons_pressed(gMainController);
    if (pressed.raw) {
        sCurrentState = STATE_CLOSE;
    }
}

static void message_box_close_update(void) {
    sScrollTop += SCROLL_SPEED;
    if (sScrollTop >= MESSAGE_BOX_Y + MESSAGE_BOX_HEIGHT) {
        message_box_reset();
    }
}

bool message_box_update(void) {
    switch (sCurrentState) {
        case STATE_OPEN:  message_box_open_update();  break;
        case STATE_SHOW:  message_box_show_update();  break;
        case STATE_CLOSE: message_box_close_update(); break;
        default: break;
    }

    return sMessageBoxActive;
}

void message_box_draw(void) {
    if (!sMessageBoxActive || !IS_VALID_MESSAGE(sCurrentMessage)) { return; }

    int height = sScrollBottom - sScrollTop;

    set_draw_color(0, 0, 0);
    draw_rectangle_filled(MESSAGE_BOX_X, sScrollTop, MESSAGE_BOX_WIDTH, height);

    set_draw_color(255, 255, 255);
    draw_rectangle_outline(MESSAGE_BOX_X, sScrollTop, MESSAGE_BOX_WIDTH, height);

    if (sCurrentState == STATE_SHOW) {
        draw_text(gTextMessages[sCurrentMessage], MESSAGE_BOX_X + PADDING, MESSAGE_BOX_Y + PADDING);
    }
}
