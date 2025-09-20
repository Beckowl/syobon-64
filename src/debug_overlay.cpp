#if DEBUG

#include <libdragon.h>
#include <stdio.h>

#include "sa_graphics.hpp"
#include "sa_input.hpp"
#include "profiler.hpp"
#include "debug_overlay.hpp"

#define OVERLAY_X 20
#define OVERLAY_Y_START 20
#define LINE_SPACING 18

static Profiler** sProfilers = NULL;
static int sNumProfilers = 0;

static bool sDrawOverlay = false;

void debug_overlay_init(Profiler** profilers, int count) {
    sProfilers = profilers;
    sNumProfilers = count;
}

void debug_overlay_update(void) {
    if (is_button_pressed(BUTTON_Z)) {
        sDrawOverlay = !sDrawOverlay;

        if (sProfilers) {
            for (int i = 0; i < sNumProfilers; i++) {
                profiler_clear(sProfilers[i]);
            }
        }
    }
}

static int draw_profilers(int x, int y) {
    for (int i = 0; i < sNumProfilers; i++) {
        Profiler *p = sProfilers[i];

        char buf[256];
        snprintf(buf, sizeof(buf), "%s: %llu us | avg: %llu us", p->name,
                 (unsigned long long)p->elapsedTime,
                 (unsigned long long)p->avgTime);

        draw_text(buf, x, y);
        y += LINE_SPACING;
    }

    return y;
}

static int draw_fps(int x, int y) {
    char buf[32];
    snprintf(buf, sizeof(buf), "FPS: %.2f", display_get_fps());
    draw_text(buf, x, y);

    return y + LINE_SPACING;
}

void debug_overlay_draw(void) {
    if (!sDrawOverlay) {
        return;
    }

    int y = OVERLAY_Y_START;

    y = draw_profilers(OVERLAY_X, y);
    y = draw_fps(OVERLAY_X, y);
}

#endif