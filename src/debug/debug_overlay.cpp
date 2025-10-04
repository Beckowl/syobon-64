#if DEBUG

#include <libdragon.h>
#include <stdio.h>

#include "sa_graphics.hpp"
#include "sa_input.hpp"
#include "profiler.hpp"
#include "debug_overlay.hpp"

#define OVERLAY_X 50
#define OVERLAY_Y_START 50
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

        draw_text_fmt(x, y, "%s: %llu us | avg: %llu us", 
            p->name,
            (unsigned long long)p->elapsedTime,
            (unsigned long long)p->avgTime
        );

        y += LINE_SPACING;
    }

    return y;
}

static int draw_fps(int x, int y) {
    draw_text_fmt(x, y, "FPS: %.2f", display_get_fps());

    return y + LINE_SPACING;
}

static int draw_heap_stats(int x, int y) {
    heap_stats_t stats;
    sys_get_heap_stats(&stats);

    float percent = (float)stats.used / (float)stats.total * 100.0f;

    draw_text_fmt(x, y, "HEAP: total: %i | used: %i (%.2f%%)", stats.total, stats.used, percent);

    return y + LINE_SPACING;
}

void debug_overlay_draw(void) {
    if (!sDrawOverlay) {
        return;
    }

    int y = OVERLAY_Y_START;

    y = draw_heap_stats(OVERLAY_X, y);
    y = draw_profilers(OVERLAY_X, y);
    y = draw_fps(OVERLAY_X, y);
}

#endif