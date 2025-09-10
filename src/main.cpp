#include <libdragon.h>
#include "controller.hpp"

#define FONT_SAZANAMI 1

void init(void) {
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);
    display_set_fps_limit(30.0f);
    rdpq_init();

    dfs_init(DFS_DEFAULT_LOCATION);
    joypad_init();
    find_main_controller();

    timer_init();
    
    rdpq_font_t *sazanami_font = rdpq_font_load("rom:/res/sazanami-gothic.font64");
    
    rdpq_fontstyle_t font_style = {
        .color = RGBA32(0xFF, 0xFF, 0xFF, 0xFF),
        .outline_color = RGBA32(0x01, 0x01, 0x01, 0xFF)
    };

    rdpq_text_register_font(FONT_SAZANAMI, sazanami_font);
    rdpq_font_style(sazanami_font, 0, &font_style);
}

void update_game(void) {
    joypad_poll();
}

void draw_game(void) {
    if (!gControllerFound) {
        rdpq_text_print(NULL, FONT_SAZANAMI, 50, 50, "NO CONTROLLER");
    } else if (is_button_down(BUTTON_A)) {
        rdpq_text_print(NULL, FONT_SAZANAMI, 50, 50, "Hello world");
    }
}

int main(void) {
    init();

    while (!exception_reset_time()) {
        update_game();

        surface_t *disp = display_get();
        rdpq_attach(disp, NULL);
        rdpq_clear(RGBA32(0x7f, 0x7f, 0x7f, 0xFF));

        draw_game();

        rdpq_detach_show();
    } 
    
    while (true) {
        __asm__ volatile("nop");
    }

    return 0;
}