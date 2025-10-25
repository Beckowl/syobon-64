#ifndef MISC_TEXT_H
#define MISC_TEXT_H

typedef enum {
    TEXT_PRESS_START,
    TEXT_NO_CONTROLLER,
    TEXT_STAGE_NUM,
    TEXT_MYSTERY_DUNGEON,
    TEXT_PAUSED,
    TEXT_CONTINUE,
    TEXT_GO_TO_TITLE,
    TEXT_GAME_CLEAR,
    TEXT_THANKS_FOR_PLAYING,
} MiscText;

// just to make it look pretty
#define MISC_TEXT(id, text) [id] = text

inline const char* gMiscText[] {
#if defined(LANG_EN)
#include "text/en/misc.hpp"
#else
#include "text/jp/misc.hpp"
#endif
};

#endif