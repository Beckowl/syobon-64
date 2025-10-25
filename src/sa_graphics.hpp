#ifndef SA_GRAPHICS_H
#define SA_GRAPHICS_H

#include <libdragon.h>

#define FONT_SAZANAMI 1
#define SCREEN_WIDTH 560
#define SCREEN_HEIGHT 420
#define FPS_TARGET 30

typedef struct {
    sprite_t* source;
    int sourceX;
    int sourceY;
    int width;
    int height;
} SpriteRegion;

#define RECENTER_X(x) ((x) + (((SCREEN_WIDTH) - (480)) / 2))
#define RESCALE_X(x) ((x) * SCREEN_WIDTH / 480)

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

// the origin of the text is the BOTTOM LEFT for some reason
// so i added a 16px y offset to make it the top left
inline void draw_text(const char* text, int x, int y) {
    rdpq_set_mode_standard();
    rdpq_text_print(NULL, FONT_SAZANAMI, x, y + 16, text);
}

void draw_text_fmt(int x, int y, const char* format, ...);
void measure_text(const char* text, uint16_t* width, uint16_t* height);

#endif
