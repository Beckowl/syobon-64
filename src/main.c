#include <libdragon.h>

void init(void) {
    dfs_init(DFS_DEFAULT_LOCATION);
    display_init(RESOLUTION_640x480, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_DISABLED);
    rdpq_init();
    joypad_init();
}

void update_game(void) { }

void draw_game(void) { }

int main(void) {
    init();

    while (!exception_reset_time()) {
        joypad_poll();
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