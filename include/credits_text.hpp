#ifndef CREDITS_TEXT_H
#define CREDITS_TEXT_H

#include "sa_graphics.hpp"

struct CreditsLine {
    const char* text;
    int yOffset;
};

#define CREDITS_LINE(text, yOffset) { text, yOffset}

const CreditsLine gCreditsText[] = {
#if defined(LANG_EN)
#include "text/en/credits.hpp"
#else
#include "text/jp/credits.hpp"
#endif
};

#define CREDITS_LINE_COUNT (sizeof(gCreditsText) / sizeof(CreditsLine))

#endif