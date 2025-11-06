#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include <libdragon.h>

void level_unload_current(void);
void level_randomize(void);
void level_load(const uint8_t* levelScript);
void level_parse_stagedate(uint8_t stagedate[17][1001]);

#endif