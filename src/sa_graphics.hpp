#ifndef SA_GRAPHICS_H
#define SA_GRAPHICS_H

#include <libdragon.h>

#define SCREEN_WIDTH 560
#define SCREEN_HEIGHT 420
#define INTERLACE_MODE INTERLACE_HALF

typedef struct {
    sprite_t* source;
    int sourceX;
    int sourceY;
    int width;
    int height;
} SpriteInfo;

#define PI 3.1415926

#define RECENTER_X(x) ((x) + (((SCREEN_WIDTH) - (480)) / 2))

void sa_graphics_init(void);
void sa_graphics_deinit(void);

void set_draw_color(color_t color);

SpriteInfo* make_sprite(sprite_t* source, int sourceX, int sourceY, int width, int height);
void free_sprite(SpriteInfo* sprite);

void draw_sprite(SpriteInfo* sprite, int x, int y, bool flipX = false, bool flipY = false);
void draw_rect(int x, int y, int width, int height);
void draw_rect_outline(int x, int y, int width, int height);
void draw_line(int x1, int y1, int x2, int y2);
void draw_circle(int x, int y, int radius);
void draw_circle_outline(int x, int y, int radius);

void draw_text(const char* text, int x, int y);

#endif
