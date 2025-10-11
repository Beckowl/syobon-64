#ifndef LEVEL_COMMANDS_H
#define LEVEL_COMMANDS_H

#include "packing.hpp"

typedef enum {
    OP_LEVEL_NOOP = 0,
    OP_LEVEL_BEGIN,
    OP_LEVEL_SCROLL_AREA,
    OP_LEVEL_TYPE,
    OP_LEVEL_MUSIC,
    OP_LEVEL_PLAYER_POS,
    OP_LEVEL_TILE,
    OP_LEVEL_TILE_RANGE,
    OP_LEVEL_DECORATION,
    OP_LEVEL_ENEMY,
    OP_LEVEL_PLATFORM,
    OP_LEVEL_CALL,
    OP_LEVEL_JUMP,
    OP_LEVEL_RETURN,
    OP_LEVEL_DUMP,
    OP_LEVEL_END,
    LEVEL_OP_COUNT,
    LEVEL_OP_MAX = LEVEL_OP_COUNT - 1
} LevelCmdOp;

// Command format: [opcode][args length][...]
#define CMD_LEN(...) ((uint8_t)sizeof((uint8_t[]){__VA_ARGS__}))
#define CMD(opcode, ...) opcode, CMD_LEN(__VA_ARGS__), __VA_ARGS__
#define CMD_NO_ARGS(opcode) opcode, 0

#define LEVEL_SCRIPT_MAGIC 0x21E338

#define LEVEL_BEGIN() \
    CMD(OP_LEVEL_BEGIN, U32(LEVEL_SCRIPT_MAGIC))


// Defines the scroll area of the level, in pixels
// width <= screen width means no scroll
#define LEVEL_SCROLL_AREA(w, h) \
    CMD(OP_LEVEL_SCROLL_AREA, U32(w), U32(h))


// Changes the level theme (e.g overworld, underground, castle)
// affects the looks of blocks, background color etc
#define LEVEL_TYPE(type) \
    CMD(OP_LEVEL_TYPE, U8(type))


#define LEVEL_MUSIC(musicId) \
    CMD(OP_LEVEL_MUSIC, U8(musicId))


// Sets the player's position.
// coordinates are in TILES.
#define LEVEL_PLAYER_POS(x, y) \
    CMD(OP_LEVEL_PLAYER_POS, F16(x), F16(y))


// Places a tile (block) in the level.
// coordinates are in TILES.
#define LEVEL_TILE(type, subtype, x, y) \
    CMD(OP_LEVEL_TILE, U16(type), U16(subtype), F16(x), F16(y))


// Fills an area with a specific tile id.
// coordinates are in TILES.
#define LEVEL_TILE_RANGE(type, subtype, x, y, w, h) \
    CMD(OP_LEVEL_TILE_RANGE, U16(type), U16(subtype), F16(x), F16(y), U16(w), U16(h))


// Places background decoration (e.g clouds, trees, grass)
// coordinates are in TILES
#define LEVEL_DECORATION(id, x, y) \
    CMD(OP_LEVEL_DECORATION, U8(id), F16(x), F16(y))


// Setups SPAWN INFO for an enemy. This tells the game what
// type of enemy and where to spawn it. This is used to represent
// enemies in levels without blowing the enemy cap (24 enemies at a time)
// coordinates are in TILES
#define LEVEL_ENEMY(type, subtype, x, y) \
    CMD(OP_LEVEL_ENEMY, U8(type), U8(subtype), F16(x), F16(y))


// Adds a platform to the level (like the ones in 1-2 or 1-3)
#define LEVEL_PLATFORM(type, subtype, fallSpeed, x, y, width) \
    CMD(OP_LEVEL_PLATFORM, U8(type), U8(subtype), U16(fallSpeed), F16(x), F16(y), F16(width))


// Calls a C function. Can be used to load levels in the old way
#define LEVEL_CALL(func) \
    CMD(OP_LEVEL_CALL, U32((uintptr_t)(func)))


// Jumps to another level script and continues execution from there
#define LEVEL_JUMP(script) \
    CMD(OP_LEVEL_JUMP, U32((uintptr_t)script))


// Returns from a previously jumped-to script
#define LEVEL_RETURN() \
    CMD_NO_ARGS(OP_LEVEL_RETURN)


// Dumps the current level to the console as a level script
#define LEVEL_DUMP() \
    CMD_NO_ARGS(OP_LEVEL_DUMP)


#define LEVEL_END() \
    CMD_NO_ARGS(OP_LEVEL_END)

#endif
