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

#include "credits/en.hpp"

#elif defined(LANG_PL)

#include "credits/pl.hpp"

#else

#include "credits/jp.hpp"

#endif
};

#define CREDITS_LINE_COUNT (sizeof(gCreditsText) / sizeof(CreditsLine))

#endif