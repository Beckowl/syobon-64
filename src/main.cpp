#include <libdragon.h>
#include "sa_graphics.h"
#include "sa_audio.h"
#include "sa_input.h"

#include "game/game.h"

void init(void) {
    dfs_init(DFS_DEFAULT_LOCATION);

    sa_graphics_init();
    sa_audio_init();
    sa_input_init();

    game_init();
}

void update(void) { 
    game_update();
}

void draw(void) {
    game_draw();
}

void deinit(void) {
    game_deinit();
    sa_input_deinit();
    sa_graphics_deinit();
}
 
int main(void) {
    init();

    while (!exception_reset_time()) {
        joypad_poll();
        process_audio();

        update();

        surface_t *disp = display_get();
        rdpq_attach(disp, NULL);

        draw();

        rdpq_detach_show();
    }

    deinit();

    while (true) {
        __asm__ volatile("nop");
    }

    return 0;
}