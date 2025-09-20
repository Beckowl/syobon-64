#include <libdragon.h>
#include "sa_graphics.h"

#define FONT_SAZANAMI 1

static color_t sDrawColor = RGBA32(0xff, 0xff, 0xff, 0xff);
static rdpq_font_t* sFont;

void sa_graphics_init(void) {
    display_init(RESOLUTION_640x480, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);
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

void set_draw_color(color_t color) {
    sDrawColor = color;
}

SpriteInfo* make_sprite(sprite_t* source, int sourceX, int sourceY, int width, int height) {
    SpriteInfo* sprite = (SpriteInfo*)malloc(sizeof(SpriteInfo));

    if (!sprite) { return NULL; }

    sprite->source = source;
    sprite->sourceX = sourceX;
    sprite->sourceY = sourceY;
    sprite->width = width;
    sprite->height = height;

    return sprite;
}

void free_sprite(SpriteInfo* sprite) {
    free(sprite);
}

void draw_sprite(SpriteInfo* sprite, int x, int y, bool flip) {
    rdpq_set_mode_standard();
    rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);
    rdpq_set_prim_color(sDrawColor);
    rdpq_mode_alphacompare(1);

    rdpq_blitparms_t parms = {
        .s0 = sprite->sourceX,
        .t0 = sprite->sourceY,
        .width = sprite->width,
        .height = sprite->height,
        .flip_x = flip,
    };

    rdpq_sprite_blit(sprite->source, x, y, &parms);
}

void draw_rect(int x, int y, int width, int height) {
    rdpq_set_mode_standard();
    rdpq_set_mode_fill(sDrawColor);

    rdpq_fill_rectangle(x, y, x + width, y + height);
}

void draw_rect_outline(int x, int y, int width, int height) {
    rdpq_set_mode_standard();
    rdpq_set_mode_fill(sDrawColor);

    rdpq_fill_rectangle(x, y, x + width, y + 1);
    rdpq_fill_rectangle(x, y + height - 1, x + width, y + height);
    rdpq_fill_rectangle(x, y, x + 1, y + height);
    rdpq_fill_rectangle(x + width - 1, y, x + width, y + height);
}

void draw_line(int x1, int y1, int x2, int y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float len = sqrtf(dx * dx + dy * dy);

    rdpq_set_mode_standard();
    rdpq_set_mode_fill(sDrawColor);

    if (len == 0) {
        rdpq_draw_pixel(x1, y1);
        return;
    }
    
    float perpX = -dy / len;
    float perpY = dx / len;

    float xOffset = perpX * 0.5f;
    float yOffset = perpY * 0.5f;

    float v1[2] = { x1 - xOffset, y1 - yOffset };
    float v2[2] = { x1 + xOffset, y1 + yOffset };
    float v3[2] = { x2 - xOffset, y2 - yOffset };
    float v4[2] = { x2 + xOffset, y2 + yOffset };

    rdpq_triangle(&TRIFMT_FILL, v1, v2, v3);
    rdpq_triangle(&TRIFMT_FILL, v2, v3, v4);
}

#define NUM_CIRCLE_SEGMENTS 32

static void get_circle_points(int cx, int cy, int radius, float points[][2]) {
    for (int i = 0; i <= NUM_CIRCLE_SEGMENTS; i++) {
        float theta = 2.0f * PI * i / NUM_CIRCLE_SEGMENTS;

        points[i][0] = cx + radius * cosf(theta);
        points[i][1] = cy + radius * sinf(theta);
    }
}

void draw_circle(int x, int y, int radius) {
    rdpq_set_mode_standard();
    rdpq_set_mode_fill(sDrawColor);

    float points[NUM_CIRCLE_SEGMENTS + 1][2];
    get_circle_points(x, y, radius, points);

    float center[2] = { (float)x, (float)y };

    for (int i = 0; i < NUM_CIRCLE_SEGMENTS; i++) {
        rdpq_triangle(&TRIFMT_FILL, center, points[i], points[i+1]);
    }
}

void draw_circle_outline(int cx, int cy, int radius) {
    rdpq_set_mode_standard();
    rdpq_set_mode_fill(sDrawColor);

    float points[NUM_CIRCLE_SEGMENTS + 1][2];
    get_circle_points(cx, cy, radius, points);

    for (int i = 0; i < NUM_CIRCLE_SEGMENTS; i++) {
        float* p1 = points[i];
        float* p2 = points[i + 1];

        draw_line(p1[0], p1[1], p2[0], p2[1]);
    }
}

void draw_text(const char* text, int x, int y) {
    rdpq_set_mode_standard();
    rdpq_text_print(NULL, FONT_SAZANAMI, x, y, text);
}