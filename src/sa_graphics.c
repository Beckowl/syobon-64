#include <libdragon.h>
#include "sa_graphics.h"

static color_t sDrawColor = RGBA32(0xff, 0xff, 0xff, 0xff);

void sa_graphics_init(void) {
    display_init(RESOLUTION_640x480, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);
    rdpq_init();
}

void set_draw_color(color_t color) {
    sDrawColor = color;
}

SpriteInfo* make_sprite(sprite_t* source, int sourceX, int sourceY, int width, int height) {
    SpriteInfo* sprite = malloc(sizeof(SpriteInfo));

    sprite->source = source;
    sprite->sourceX = sourceX;
    sprite->sourceY = sourceY;
    sprite->width = width;
    sprite->height = height;

    return sprite;
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
    rdpq_mode_combiner(RDPQ_COMBINER_FLAT);
    rdpq_set_prim_color(sDrawColor);

    rdpq_fill_rectangle(x, y, x + width, y + height);
}

void draw_rect_outline(int x, int y, int width, int height) {
    rdpq_set_mode_standard();
    rdpq_mode_combiner(RDPQ_COMBINER_FLAT);
    rdpq_set_prim_color(sDrawColor);

    rdpq_fill_rectangle(x, y, x + width, y + 1);
    rdpq_fill_rectangle(x, y + height - 1, x + width, y + height);
    rdpq_fill_rectangle(x, y, x + 1, y + height);
    rdpq_fill_rectangle(x + width - 1, y, x + width, y + height);
}
