#include <libdragon.h>

#include "level_script.hpp"
#include "level_commands.hpp"
#include "global.hpp"
#include "states/play.hpp"

#include "sa_audio.hpp"
#include "sa_graphics.hpp"
#include "packing.hpp"

static const uint8_t* sCurrCmd;
static const uint8_t* sJumpStack[32];
static int8_t sJumpStackTop = 0;

#define PARAM_U8(offset)   read_u8(sCurrCmd + 2 + (offset))
#define PARAM_U16(offset)  read_u16(sCurrCmd + 2 + (offset))
#define PARAM_U32(offset)  read_u32(sCurrCmd + 2 + (offset))

#define PARAM_S8(offset)  (int8_t)PARAM_U8(offset)
#define PARAM_S16(offset) (int16_t)PARAM_U16(offset)
#define PARAM_S32(offset) (int32_t)PARAM_U32(offset)

#define PARAM_F16(offset) read_f16(sCurrCmd + 2 + (offset))

#define TILES_TO_PIXELS(x, y) (int)((x) * 29), (int)((y) * 29 - 12)

#define CMD_NEXT (sCurrCmd + 2 + sCurrCmd[1])

static bool level_header_valid(void) {
    if (sCurrCmd[0] != OP_LEVEL_BEGIN) {
        return false;
    }

    uint32_t magic = PARAM_U32(0);
    
    if (magic != LEVEL_SCRIPT_MAGIC) {
        return false;
    }

    return true;
}

static void level_cmd_scroll_area(void) {
    uint16_t w = PARAM_U16(0);
    uint16_t h = PARAM_U16(2);

    scrollx = (w - SCREEN_WIDTH) * 100;
    scrolly = (h - SCREEN_HEIGHT) * 100;

    sCurrCmd = CMD_NEXT;
}

static void level_cmd_set_type(void) {
    uint8_t type = PARAM_U8(0);
    stagecolor = type;

    sCurrCmd = CMD_NEXT;
}

static void level_cmd_set_music(void) {
    uint8_t id = PARAM_U8(0);

    if (otom[id]) {
        set_background_music(otom[id]);
    }

    sCurrCmd = CMD_NEXT;
}

static void level_cmd_player_pos(void) {
    float_t x = PARAM_F16(0);
    float_t y = PARAM_F16(4);

    ma = (int)(x * 29);
    mb = (int)(y * 29 - 12);

    sCurrCmd = CMD_NEXT;
}

static void level_cmd_tile(void) {
    uint16_t type = PARAM_U16(0);
    uint16_t subtype = PARAM_U16(2);
    float_t x = PARAM_F16(4);
    float_t y = PARAM_F16(8);

    txtype[tco] = subtype;

    tyobi(TILES_TO_PIXELS(x, y), type);
    sCurrCmd = CMD_NEXT;
}

static void level_cmd_tile_range(void) {
    uint16_t type = PARAM_U16(0);
    uint16_t subtype = PARAM_U16(2);
    float_t startX = PARAM_F16(4);
    float_t startY = PARAM_F16(8);
    uint16_t width = PARAM_U16(12);
    uint16_t height = PARAM_U16(14);

    for (uint16_t x = 0; x < width; x++) {
        for (uint16_t y = 0; y < height; y++) {
            txtype[tco] = subtype;

            tyobi(TILES_TO_PIXELS(startX + x, startY + y), type);
        }
    }

    sCurrCmd = CMD_NEXT;
}

static void level_cmd_decoration(void) {
    uint16_t type = PARAM_U8(0);
    float_t x = PARAM_F16(1);
    float_t y = PARAM_F16(5);

    spawn_decoration(type, TILES_TO_PIXELS(x, y));
    sCurrCmd = CMD_NEXT;
}

static void level_cmd_enemy(void) {
    uint8_t type = PARAM_U8(0);
    uint8_t subtype = PARAM_U8(1);
    float_t x = PARAM_F16(2);
    float_t y = PARAM_F16(6);

    set_enemy_spawn(type, subtype, TILES_TO_PIXELS(x, y));
    sCurrCmd = CMD_NEXT;
}

static void level_cmd_platform(void) {
    uint8_t type = PARAM_U8(0);
    uint8_t subtype = PARAM_U8(1);
    float_t fallSpeed = PARAM_U16(2);
    float_t x = PARAM_F16(4);
    float_t y = PARAM_F16(8);
    uint8_t width = PARAM_F16(12);

    spawn_platform(type, subtype, fallSpeed, TILES_TO_PIXELS(x, y), width * 29);
    sCurrCmd = CMD_NEXT;
}

static void level_cmd_object(void) {
    uint16_t type = PARAM_U16(0);
    uint8_t subtype = PARAM_U8(2);
    float_t x = PARAM_F16(3);
    float_t y = PARAM_F16(7);
    int16_t width = PARAM_S16(11);
    int16_t height = PARAM_S16(13);

    spawn_general_object(type, subtype, TILES_TO_PIXELS(x, y), width, height);
    sCurrCmd = CMD_NEXT;
}

static void level_cmd_call(void) {
    uintptr_t funcPtr = (uintptr_t)PARAM_U32(0);
    void (*func)(void) = (void(*)(void))funcPtr;

    if (func) {
        func();
    }

    sCurrCmd = CMD_NEXT;
}

static void level_cmd_jump(void) {
    const uint8_t* target = (const uint8_t*)PARAM_U32(0);

    if (sJumpStackTop >= 32) {
        debugf("Level jump stack overflow\n");
        sCurrCmd = NULL;
        return;
    }

    sJumpStack[sJumpStackTop++] = CMD_NEXT;

    sCurrCmd = target;
}

static void level_cmd_return(void) {
    if (sJumpStackTop <= 0) {
        sCurrCmd = NULL;
        return;
    }

    sCurrCmd = sJumpStack[--sJumpStackTop];
}

void (*LevelCommandTable[LEVEL_OP_COUNT])(void) = {
    NULL, // OP_LEVEL_NOOP
    NULL, // OP_LEVEL_BEGIN (it's just a header)
    level_cmd_scroll_area,
    level_cmd_set_type,
    level_cmd_set_music,
    level_cmd_player_pos,
    level_cmd_tile,
    level_cmd_tile_range,
    level_cmd_decoration,
    level_cmd_enemy,
    level_cmd_platform,
    level_cmd_object,
    level_cmd_call,
    level_cmd_jump,
    level_cmd_return,
    NULL, // OP_LEVEL_DUMP
    NULL, // OP_LEVEL_END
};

LevelScriptResult level_script_execute(const uint8_t* script) {
    LevelScriptResult result = {
        .status = LEVEL_SCRIPT_SUCCESS,
        .index = 0
    };

    if (!script) {
        result.status = LEVEL_SCRIPT_NO_SCRIPT;
        return result;
    }

    sCurrCmd = script;
    sJumpStackTop = 0;

    if (!level_header_valid()) {
        result.status = LEVEL_SCRIPT_INVALID_HEADER;
        return result;
    }

    while (sCurrCmd) {
        uint8_t opcode = sCurrCmd[0];
        result.index = (size_t)(sCurrCmd - script);

        if (opcode == OP_LEVEL_END) {
            result.status = LEVEL_SCRIPT_SUCCESS;
            break;
        }

        if (opcode > LEVEL_OP_MAX) {
            // your level script is fucked up
            result.status = LEVEL_SCRIPT_INVALID_OP;
            break;
        }

        if (LevelCommandTable[opcode]) {
            LevelCommandTable[opcode]();
        } else {
            sCurrCmd = CMD_NEXT;
        }
    }

    return result;
}
