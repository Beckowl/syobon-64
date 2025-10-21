#ifndef CREDITS_TEXT_H
#define CREDITS_TEXT_H

#include "sa_graphics.hpp"

struct CreditsLine {
    const char* text;
    int yOffset;
};

#define CREDITS_LINE(text, yOffset) { text, yOffset}

CreditsLine gCreditsText[] = {
#include "text/jp/credits.hpp"
};

#define CREDITS_LINE_COUNT (sizeof(gCreditsText) / sizeof(CreditsLine))

#endif