#if DEBUG

#include <libdragon.h>

#include "profiler.hpp"

void profiler_init(Profiler* p, const char* name) {
    p->name = name;
    p->elapsedTime = 0;
    p->totalTime = 0;
    p->avgTime = 0;
    p->numCalls = 0;
}

void profiler_start(Profiler* p) {
    p->startTime = get_ticks_us();
}

void profiler_clear(Profiler* p) {
    p->elapsedTime = 0;
    p->avgTime = 0;
    p->numCalls = 0;
    p->totalTime = 0;
}

void profiler_end(Profiler* p) {
    uint64_t endTime = get_ticks_us();
    p->elapsedTime = endTime - p->startTime;
    
    p->totalTime += p->elapsedTime;
    p->numCalls++;
    p->avgTime = p->totalTime / p->numCalls;
}

#endif