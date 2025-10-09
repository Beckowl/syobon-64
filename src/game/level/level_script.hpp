#ifndef LEVEL_SCRIPT_H
#define LEVEL_SCRIPT_H

#include <libdragon.h>

typedef enum {
    LEVEL_SCRIPT_SUCCESS = 0,
    LEVEL_SCRIPT_NO_SCRIPT = 1,
    LEVEL_SCRIPT_INVALID_HEADER = 2,
    LEVEL_SCRIPT_INVALID_OP = 3,
} LSErrorCode;

typedef struct {
    LSErrorCode status;
    size_t index;
} LevelScriptResult;

LevelScriptResult level_script_execute(const uint8_t* script);

#endif