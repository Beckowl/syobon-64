#ifndef CREDITS_TEXT_H
#define CREDITS_TEXT_H

#include "sa_graphics.hpp"

struct CreditsLine {
    const char* text;
    int xPos;
    int yOffset;
};

#define CENTER_LINE(length) ((SCREEN_WIDTH / 2) - ((length) * 20 / 2))
#define CREDITS_LINE(text, length, yOffset) { text, CENTER_LINE(length), yOffset}

CreditsLine gCreditsText[] = {
#if defined(LANG_EN)

#include "en/credits.hpp"

#elif defined(LANG_PL)

#include "pl/credits.hpp"

#else

#include "jp/credits.hpp"

#endif
};

#define CREDITS_LINE_COUNT (sizeof(gCreditsText) / sizeof(CreditsLine))

#endif