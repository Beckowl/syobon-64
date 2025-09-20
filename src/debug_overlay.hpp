#ifndef DEBUG_OVERLAY_H
#define DEBUG_OVERLAY_H

#include "profiler.hpp"

#if DEBUG

void debug_overlay_init(Profiler** profilers, int count);
void debug_overlay_update(void);
void debug_overlay_draw(void);

#else

#define debug_overlay_init(profilers, count)
#define debug_overlay_update()
#define debug_overlay_draw()

#endif

#endif