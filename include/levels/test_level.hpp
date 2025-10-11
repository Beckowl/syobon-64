#include <libdragon.h>

#include "level_commands.hpp"
#include "level_enums.hpp"

void test_func(void) {
    debugf("Hello from test level!\n");
}

const uint8_t testLevelStuff[] = {
    LEVEL_TILE_RANGE(TILE_HARD_BLOCK, 0, 0, 13, 20, 2),

    // half tiles are allowed!!
    LEVEL_TILE(TILE_TRAMPOLINE_BROKEN, 0, 14.5, 12),

    LEVEL_DECORATION(DECORATION_CASTLE, 1, 10),
    LEVEL_DECORATION(DECORATION_CLOUD, 14, 4),

    LEVEL_ENEMY(ENEMY_CHICKEN, 0, 10, 11),

    LEVEL_RETURN(),
};

const uint8_t testLevel[] = {
    LEVEL_BEGIN(),
        LEVEL_TYPE(LEVEL_TYPE_OVERWORLD),
        LEVEL_SCROLL_AREA(0, 0),
        LEVEL_MUSIC(MUSIC_OVERWORLD),

        LEVEL_PLAYER_POS(2, 11),

        LEVEL_CALL(test_func),

        LEVEL_JUMP(testLevelStuff),

        LEVEL_TILE(TILE_ITEM_BLOCK_ENEMY, 4, 5, 9),
        LEVEL_PLATFORM(PLATFORM_GRAY, 0, 0, 10, 9, 3),
    LEVEL_END(),
};