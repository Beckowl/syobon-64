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
} SpriteRegion;

#define PI 3.1415926

#define RECENTER_X(x) ((x) + (((SCREEN_WIDTH) - (480)) / 2))
#define RESCALE_X(x) ((x) * SCREEN_WIDTH / 480)
#define IS_OFFSCREEN(x, y, w, h) (((x)+(w) <= 0) || ((x) >= SCREEN_WIDTH) || ((y)+(h) <= 0) || ((y) >= SCREEN_HEIGHT))

void sa_graphics_init(void);

void sa_graphics_clear(void);

void set_draw_color(color_t color);
void set_draw_color(uint8_t r=255, uint8_t g=255, uint8_t b=255);

SpriteRegion* get_sprite_region(sprite_t* source, int sourceX, int sourceY, int width, int height);

void draw_sprite_region(SpriteRegion* sprite, int x, int y, bool flipX = false, bool flipY = false);
void draw_rectangle_filled(int x, int y, int width, int height);
void draw_rectangle_outline(int x, int y, int width, int height);
void draw_line(int x1, int y1, int x2, int y2);
void draw_circle_filled(int x, int y, int radius);
void draw_circle_outline(int x, int y, int radius);

void draw_text(const char* text, int x, int y);
void draw_text_fmt(int x, int y, const char* format, ...);
void measure_text(const char* text, uint16_t* width, uint16_t* height);

#endif
