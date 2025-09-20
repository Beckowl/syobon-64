#include <libdragon.h>
#include "sa_graphics.h"
#include "sa_audio.h"
#include "sa_input.h"

#include "game/main.h"

void init(void) {
    dfs_init(DFS_DEFAULT_LOCATION);
    sa_graphics_init();
    sa_audio_init();
    sa_input_init();

    loadg();
}

void update_game(void) { }

void draw_game(void) {
    DrawString(50, 50, "hello", 0);
    DrawGraph(100, 100, grap[16][1], 0);
    DrawTurnGraph(130, 100, grap[0][0], 0);
 }

int main(void) {
    init();

    while (!exception_reset_time()) {
        joypad_poll();
        process_audio();
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