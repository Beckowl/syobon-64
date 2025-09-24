#include <libdragon.h>

#include "sa_graphics.hpp"
#include "sa_audio.hpp"
#include "sa_input.hpp"
#include "profiler.hpp"
#include "debug_overlay.hpp"

#include "game/game.hpp"

Profiler sRenderProfiler;
static Profiler sUpdateProfiler;
static Profiler* sProfilers[] = { &sRenderProfiler, &sUpdateProfiler };

void init(void) {
    srand(getentropy32());
    
    dfs_init(DFS_DEFAULT_LOCATION);

    sa_graphics_init();
    sa_audio_init();
    sa_input_init();

    game_init();

    profiler_init(&sRenderProfiler, "RENDER");
    profiler_init(&sUpdateProfiler, "UPDATE");

    debug_overlay_init(sProfilers, 2);
}

void update(void) { 
    profiler_start(&sUpdateProfiler);

    game_update();

    profiler_end(&sUpdateProfiler);
}

void draw(void) {
    profiler_start(&sRenderProfiler);

    game_draw();

    profiler_end(&sRenderProfiler);
}

void deinit(void) {
    game_deinit();
    sa_input_deinit();
    sa_graphics_deinit();
}
 
int main(void) {
    init();

    while (true) {
        joypad_poll();
        process_audio();

        update();
        debug_overlay_update();

        surface_t *disp = display_get();
        rdpq_attach(disp, NULL);

        draw();
        debug_overlay_draw();

        rdpq_detach_show();
    }

    deinit();

    return 0;
}