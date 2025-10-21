#include <libdragon.h>

#include "level_loader.hpp"
#include "level_script.hpp"
#include "level_commands.hpp"
#include "level_enums.hpp"

#include "states/play.hpp"
#include "global.hpp"

// THIS IS CHIKU'S CODE
// these arrays should've been structs smh smh
void level_unload_current(void) {
    for (t = 0; t < smax; t++) {
        sa[t] = -9000000;
        sb[t] = 1;
        sc[t] = 1;
        sd[t] = 1;
        sgtype[t] = 0;
        stype[t] = 0;
        sxtype[t] = 0;
    }

    for (t = 0; t < tmax; t++) {
        ta[t] = -9000000;
        tb[t] = 1;
        titem[t] = 0;
        txtype[t] = 0;
    }

    for (t = 0; t < srmax; t++) {
        sra[t] = -9000000;
        srb[t] = 1;
        src[t] = 1;
        srd[t] = 1;
        sre[t] = 0;
        srf[t] = 0;
        srmuki[t] = 0;
        sron[t] = 0;
        srsok[t] = 0;
        srmove[t] = 0;
        srmovep[t] = 0;
        srsp[t] = 0;
    }

    for (t = 0; t < amax; t++) {
        aa[t] = -9000000;
        ab[t] = 1;
        ac[t] = 0;
        ad[t] = 1;
        azimentype[t] = 0;
        atype[t] = 0;
        axtype[t] = 0;
        ae[t] = 0;
        af[t] = 0;
        atm[t] = 0;
        abrocktm[t] = 0;
        amsgtm[t] = 0;
    }

    for (t = 0; t < bmax; t++) {
        ba[t] = -9000000;
        bb[t] = 1;
        bz[t] = 1;
        btm[t] = 0;
        bxtype[t] = 0;
    }

    for (t = 0; t < emax; t++) {
        ea[t] = -9000000;
        eb[t] = 1;
        ec[t] = 1;
        ed[t] = 1;
        egtype[t] = 0;
    }

    for (t = 0; t < nmax; t++) {
        na[t] = -9000000;
        nb[t] = 1;
        ne[t] = 1;
        nf[t] = 1;
        ntype[t] = 0;
    }

    scrollx = 3600 * 100;
    stagecolor = 1;   
    fx = 0;
    fy = 0;
    stageonoff = 0;
    sco = 0;
    tco = 0;
    aco = 0;
    bco = 0;
    eco = 0;
    nco = 0;
    srco = 0; // did they forget to reset this?
}

void level_randomize(void) {
    // randomize blocks
    for (int i = 0; i < tmax; i++) {
        if (rand(3) <= 1) {
            ta[i] = (rand(500) - 1) * 29 * 100;
            tb[i] = rand(14) * 100 * 29 - 1200;

            ttype[i] = rand(142); // 142?? most of these ids are just air!

            if (ttype[i] >= 9 && ttype[i] <= 99) {
                ttype[i] = rand(8);
            }

            txtype[i] = rand(4);
        }
    }

    // randomize enemies
    for (int i = 0; i < bmax; i++) {
        if (rand(2) <= 1) {
            ba[i] = (rand(500) - 1) * 29 * 100;
            bb[i] = rand(15) * 100 * 29 - 1200 - 3000;

            if (rand(6) == 0) {
                btype[i] = rand(9);
            }
        }
    }

    // spawn a platform under the player
    spawn_platform(PLATFORM_YELLOW, 0, 0, (ma+fx)/100, (13 * 29 - 12), 30);

    // change level palette if lucky
    if (rand(4) == 0) {
        stagecolor = rand(5);
    }
}

static void level_parse_stagedate(void) {
    for (tt = 0; tt <= 1000; tt++) {
        for (t = 0; t <= 16; t++) {
            int tileType = stagedate[t][tt];
            int xPos = tt * 29;
            int yPos = t * 29 - 12;

            if (tileType >= 1 && tileType <= 19 && tileType != 9) {
                tyobi(tt * 29, t * 29 - 12, tileType);
            }

            if (tileType >= 20 && tileType <= 29) {
                spawn_platform(PLATFORM_YELLOW, 0, 0, xPos, yPos, 30);
            }

            if (tileType == 30) {
                spawn_general_object(OBJECT_CHECKPOINT, 0, xPos, yPos, 30, 60);
            }

            if (tileType == 40) {
                spawn_general_object(OBJECT_VERTICAL_PIPE_HEAD, 0, xPos, yPos, 60, 30);
            }

            if (tileType == 41) {
                spawn_general_object(OBJECT_PIPE_BODY, 0, xPos + 5, yPos, 50, 30);
            }

            if (tileType == 43) {
                // isn't this supposed to be a horizontal pipe body?
                spawn_general_object(OBJECT_VERTICAL_PIPE_HEAD, 0, xPos, yPos + 5, 29, 53);
            }

            if (tileType == 44) {
                spawn_general_object(OBJECT_HORIZONTAL_PIPE_HEAD, 0, xPos, yPos + 7, 39, 50);
            }

            // これなぜかバグの原因ｗ
            if (tileType >= 50 && tileType <= 79) {
                set_enemy_spawn(tileType - 50, 0, xPos, yPos);
            }

            if (tileType >= 80 && tileType <= 89) {
                spawn_decoration(tileType - 80, xPos, yPos);
            }

            // コイン
            if (tileType == 9) {
                tyobi(tt * 29, t * 29 - 12, 800);
            }

            if (tileType == 99) {
                spawn_general_object(OBJECT_GOAL_POLE, 0, xPos, yPos, 30, (12 - t) * 30);
            }
        }
    }
}

static void level_script_dump(const uint8_t* script) {
    unsigned int index = 0;

    debugf("\n---- LEVEL SCRIPT DUMP ----\n\n");

    while (true) {
        uint8_t opcode = script[index];
        uint8_t argLen = script[index + 1];

        debugf("%04X: %02X %02X ", index, opcode, argLen);

        for (int i = 0; i < argLen; i++) {
            debugf("%02X ", script[index + 2 + i]);
        }

        debugf("\n");

        index += 2 + argLen;

        if (opcode == OP_LEVEL_END)
            break;
    }

    debugf("\n---- END OF SCRIPT DUMP ----\n\n");
}

void level_load(const uint8_t* levelScript) {
    debugf("Loading level %p\n", (void*)levelScript);

    level_unload_current();

    uint64_t time = get_ticks_us();
    LevelScriptResult result = level_script_execute(levelScript);

    if (result.status != LEVEL_SCRIPT_SUCCESS) {
        debugf("Level script execution failed! status: %02x, index: %x\n", result.status, result.index);

        level_script_dump(levelScript);
        return;
    }

    level_parse_stagedate();
    player_init_checkpoint();

    // over means mystery dungeon (randomized levels) mode is enabled
    if (over) {
        level_randomize();
    }

    debugf("Level loaded in %llu microseconds.\n", get_ticks_us() - time);
}
