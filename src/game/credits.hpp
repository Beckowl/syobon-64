#ifndef CREDITS_H
#define CREDITS_H

struct CreditsLine {
    const char* text;
    int xPos;
    int yOffset;
};

#define CENTER_LINE(length) ((SCREEN_WIDTH / 2) - length * 20 / 2)
#define CREDITS_LINE(text, length, yOffset) { text, CENTER_LINE(length), yOffset}

void credits_enter(void);
void credits_exit(void);
void credits_update(void);
void credits_draw(void);

#endif