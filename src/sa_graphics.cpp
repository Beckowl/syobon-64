#include <libdragon.h>
#include "sa_graphics.hpp"

#define FONT_SAZANAMI 1

static color_t sDrawColor = RGBA32(0xff, 0xff, 0xff, 0xff);
static rdpq_font_t* sFont;

void sa_graphics_init(void) {
    resolution_t resolution = {
        .width = SCREEN_WIDTH,
        .height = SCREEN_HEIGHT,
        .interlaced = INTERLACE_MODE,
    };

    display_init(resolution, DEPTH_16_BPP, is_memory_expanded() ? 3 : 2, GAMMA_NONE, FILTERS_RESAMPLE);
    rdpq_init();

    sFont = rdpq_font_load("rom:/res/sazanami-gothic.font64");

    rdpq_fontstyle_t style = {
        .color = RGBA32(0xFF, 0xFF, 0xFF, 0xFF),
        .outline_color = RGBA32(0x00, 0x00, 0x00, 0xFF)
    };

    rdpq_font_style(sFont, FONT_SAZANAMI, &style);
    rdpq_text_register_font(FONT_SAZANAMI, sFont);

    display_set_fps_limit(30);
}

void sa_graphics_deinit(void) {
    rdpq_text_unregister_font(FONT_SAZANAMI);
    rdpq_font_free(sFont);

    rdpq_close();
    display_close();
}

void sa_graphics_clear(void) {
    rdpq_clear(sDrawColor);
}

void set_draw_color(color_t color) {
    sDrawColor = color;
}

void set_draw_color(uint8_t r, uint8_t g, uint8_t b) {
    sDrawColor = RGBA32(r, g, b, 255);
}

SpriteRegion* get_sprite_region(sprite_t* source, int sourceX, int sourceY, int width, int height) {
    SpriteRegion* sprite = (SpriteRegion*)malloc(sizeof(SpriteRegion));

    if (!sprite) { return NULL; }

    sprite->source = source;
    sprite->sourceX = sourceX;
    sprite->sourceY = sourceY;
    sprite->width = width;
    sprite->height = height;

    return sprite;
}

void draw_sprite_region(SpriteRegion* sprite, int x, int y, bool flipX, bool flipY) {
    if (!sprite) { return; }

    if (IS_OFFSCREEN(x, y, sprite->width, sprite->height)) { return; }

    rdpq_set_mode_standard();
    rdpq_mode_alphacompare(1);

    rdpq_blitparms_t parms = {
        .s0 = sprite->sourceX,
        .t0 = sprite->sourceY,
        .width = sprite->width,
        .height = sprite->height,
        .flip_x = flipX,
        .flip_y = flipY,
    };

    rdpq_sprite_blit(sprite->source, x, y, &parms);
}

void draw_rectangle_filled(int x, int y, int width, int height) {
    if (IS_OFFSCREEN(x, y, width, height)) { return; }

    rdpq_set_mode_standard();
    rdpq_set_mode_fill(sDrawColor);

    rdpq_fill_rectangle(x, y, x + width, y + height);
}

void draw_rectangle_outline(int x, int y, int width, int height) {
    if (IS_OFFSCREEN(x, y, width, height)) { return; }
    
    rdpq_set_mode_standard();
    rdpq_set_mode_fill(sDrawColor);

    rdpq_fill_rectangle(x, y, x + width, y + 1);
    rdpq_fill_rectangle(x, y + height - 1, x + width, y + height);
    rdpq_fill_rectangle(x, y, x + 1, y + height);
    rdpq_fill_rectangle(x + width - 1, y, x + width, y + height);
}

void draw_line(int x1, int y1, int x2, int y2) {
    rdpq_set_mode_standard();
    rdpq_mode_combiner(RDPQ_COMBINER_FLAT);
    rdpq_set_prim_color(sDrawColor);

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (true) {
        rdpq_draw_pixel(x1, y1);

        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

#define NUM_CIRCLE_POINTS 8

static void get_circle_points(int cx, int cy, int radius, float points[][2]) {
    for (int i = 0; i < NUM_CIRCLE_POINTS; i++) {
        float theta = (2 * PI / NUM_CIRCLE_POINTS) * i;

        float dx = radius * cos(theta);
        float dy = radius * sin(theta);

        points[i][0] = cx + dx;
        points[i][1] = cy + dy;
    }
}

void draw_circle_filled(int x, int y, int radius) {
    if (IS_OFFSCREEN(x - radius, y - radius, radius * 2, radius * 2)) { return; }

    rdpq_set_mode_standard();
    rdpq_mode_combiner(RDPQ_COMBINER_FLAT);
    rdpq_set_prim_color(sDrawColor);

    float center[2] = { (float)x, (float)y };
    float points[NUM_CIRCLE_POINTS][2];
    
    get_circle_points(x, y, radius, points);

    for (int i = 0; i < NUM_CIRCLE_POINTS; i++) {
        int next = (i + 1) % NUM_CIRCLE_POINTS;
        rdpq_triangle(&TRIFMT_FILL, center, points[i], points[next]);
    }
}

void draw_circle_outline(int x, int y, int radius) {
    if (IS_OFFSCREEN(x - radius, y - radius, radius * 2, radius * 2)) { return; }

    float points[NUM_CIRCLE_POINTS][2];
    
    get_circle_points(x, y, radius, points);

    for (int i = 0; i < NUM_CIRCLE_POINTS; i++) {
        int next = (i + 1) % NUM_CIRCLE_POINTS;

        float* p1  = points[i];
        float* p2 = points[next];
        draw_line(p1[0], p1[1], p2[0], p2[1]);
    }
}

void draw_text(const char* text, int x, int y) {
    rdpq_set_mode_standard();
    rdpq_text_print(NULL, FONT_SAZANAMI, x, y, text);
}

void draw_text_fmt(int x, int y, const char* format, ...) {
    rdpq_set_mode_standard();

    va_list args;
    va_start(args, format);

    rdpq_text_vprintf(NULL, FONT_SAZANAMI, x, y, format, args);

    va_end(args);
}