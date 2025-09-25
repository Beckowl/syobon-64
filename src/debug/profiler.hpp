#ifndef PROFILER_H
#define PROFILER_H

#include <libdragon.h>

typedef struct {
    const char* name;
    uint64_t startTime;
    uint64_t elapsedTime;
    uint64_t avgTime;

    uint64_t totalTime;
    uint64_t numCalls;
} Profiler;

#ifdef DEBUG

void profiler_init(Profiler* p, const char* name);
void profiler_start(Profiler* p);
void profiler_clear(Profiler* p);
void profiler_end(Profiler* p);

#else

#define profiler_init(p, name)
#define profiler_start(p)
#define profiler_clear(p)
#define profiler_end(p)

#endif

#endif