#include <libdragon.h>

#include "pause_menu.hpp"
#include "game.hpp"
#include "global.hpp"
#include "states/title_screen.hpp"
#include "states/transition.hpp"

#include "sa_graphics.hpp"
#include "sa_input.hpp"
#include "sa_audio.hpp"

static bool sMenuOpen = false;
static uint8_t sSelectIndex = 0;

#define MENU_WIDTH 240
#define MENU_HEIGHT 140
#define PADDING 6

void menu_opt_continue(void);
void menu_opt_title(void);

typedef struct {
    const char* text;
    void (*callback)(void);
} MenuOption;

static const MenuOption sMenuOptions[] = {
    {"Continue", menu_opt_continue},
    {"Go to title screen", menu_opt_title},
};

#define MENU_OPT_COUNT (sizeof(sMenuOptions) / sizeof(sMenuOptions[0]))

void menu_opt_continue(void) {
    sMenuOpen = false;
    play_sound_effect(oto[19]);
}

void menu_opt_title(void) {
    sMenuOpen = false;
    stop_background_music();
    stop_sound_effects();
    play_transition(&STATE_TITLE_SCREEN, 20, false);
}

void pause_menu_open(void) {
    sMenuOpen = true;
    sSelectIndex = 0;

    stop_sound_effects();
    play_sound_effect(oto[19]);
}

bool pause_menu_update(void) {
    if (!sMenuOpen) { return false; }

    if (is_button_pressed(BUTTON_D_DOWN) && sSelectIndex < MENU_OPT_COUNT - 1) {
        sSelectIndex++;
    }

    if (is_button_pressed(BUTTON_D_UP) && sSelectIndex > 0) {
        sSelectIndex--;
    }

    if (is_button_pressed(BUTTON_A | BUTTON_START)) {
        sMenuOptions[sSelectIndex].callback();
    }

    return sMenuOpen;
}

void pause_menu_draw(void) {
    if (!sMenuOpen) { return; }

    const int menuX = (SCREEN_WIDTH - MENU_WIDTH) / 2;
    const int menuY = (SCREEN_HEIGHT - MENU_HEIGHT) / 2;
    const int lineSpacing = 30;

    set_draw_color(0, 0, 0);
    draw_rectangle_filled(menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
    
    set_draw_color(255, 255, 255);
    draw_rectangle_outline(menuX, menuY, MENU_WIDTH, MENU_HEIGHT);

    const char* headerText = "PAUSED";
    
    uint16_t headerWidth, headerHeight;
    measure_text(headerText, &headerWidth, &headerHeight);

    draw_text(headerText, menuX + (MENU_WIDTH - headerWidth) / 2, menuY + PADDING);

    for (uint8_t i = 0; i < MENU_OPT_COUNT; i++) {
        int optY = menuY + headerHeight * 2 + i * lineSpacing;

        if (i == sSelectIndex) {
            draw_text(">", menuX + PADDING + 5, optY);
        }

        draw_text(sMenuOptions[i].text, menuX + PADDING + 25, optY);
    }

    SpriteRegion* playerSprite = grap[0][0];

    const int livesX = menuX + (MENU_WIDTH - 90) / 2;
    int livesY = menuY + MENU_HEIGHT - playerSprite->height - PADDING;

    draw_sprite_region(playerSprite, livesX, livesY);
    draw_text_fmt(livesX + 25, livesY + 10, " × %d", nokori);
}