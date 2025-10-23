#ifndef MESSAGE_TEXT_H
#define MESSAGE_TEXT_H

#include <libdragon.h>

typedef enum {
    MESSAGE_NONE = -1,
    MESSAGE_000 = 0,
    MESSAGE_001,
    MESSAGE_002,
    MESSAGE_003,
    MESSAGE_004,
    MESSAGE_005,
    MESSAGE_006,
    MESSAGE_007,
    MESSAGE_008,
    MESSAGE_009,
    MESSAGE_010,
    MESSAGE_011,
    MESSAGE_COUNT,
    MESSAGE_MAX = MESSAGE_COUNT - 1,
} TextMessageId;

#define TEXT_MESSAGE(id, text) \
    [id] = text

inline const char *gTextMessages[MESSAGE_COUNT] = {
#if defined(LANG_EN)
#include "text/en/message.hpp"
#else
#include "text/jp/message.hpp"
#endif
};

#endif