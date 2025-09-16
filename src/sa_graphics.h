#ifndef SA_GRAPHICS_H
#define SA_GRAPHICS_H

#include <libdragon.h>

typedef struct {
    sprite_t* source;
    int sourceX;
    int sourceY;
    int width;
    int height;
} SpriteInfo;

void sa_graphics_init(void);

void set_draw_color(color_t color);

SpriteInfo* make_sprite(sprite_t* source, int sourceX, int sourceY, int width, int height);

void draw_sprite(SpriteInfo* sprite, int x, int y, bool flip);
void draw_rect(int x, int y, int width, int height);
void draw_rect_outline(int x, int y, int width, int height);

#endif
