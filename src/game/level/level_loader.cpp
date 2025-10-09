#include <libdragon.h>

#include "level_loader.hpp"
#include "level_script.hpp"
#include "level_commands.hpp"

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
        tc[t] = 1;
        td[t] = 1;
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
        sree[t] = 0;
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
        a2tm[t] = 0;
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
        nc[t] = 1;
        nd[t] = 1;
        ne[t] = 1;
        nf[t] = 1;
        ng[t] = 0;
        ntype[t] = 0;
    }

    scrollx = 3600 * 100;
    stagecolor = 1;   
    fx = 0;
    fy = 0;
    fzx = 0;
    stageonoff = 0;
    sco = 0;
    tco = 0;
    aco = 0;
    bco = 0;
    eco = 0;
    nco = 0;
    srco = 0; // did they forget to reset this?
}

// randomizes a level (for mystery dungeon)
void level_shuffle(void) {
    // randomize blocks
    for (int i = 0; i < tmax; i++) {
        if (rand(3) <= 1) {
            ta[i] = (rand(500) - 1) * 29 * 100;
            tb[i] = rand(14) * 100 * 29 - 1200;

            ttype[i] = rand(142); // 142?? most of these ids are just air!

            // most of these ids aren't even blocks, wtf
            if (ttype[t] >= 9 && ttype[t] <= 99) {
                ttype[t] = rand(8);
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
    sra[0] = ma + fx;
    srb[0] = (13 * 29 - 12) * 100;
    src[0] = 30 * 100;
    srtype[0] = 0;
    sracttype[0] = 0;
    sre[0] = 0;
    srsp[0] = 0;

    srco = 1;

    // change level palette if lucky
    if (rand(4) == 0) {
        stagecolor = rand(5);
    }
}

void level_load(const uint8_t* levelScript) {
    debugf("Loading level %p\n", (void*)levelScript);

    level_unload_current();

    uint64_t time = get_ticks_us();
    LevelScriptResult result = level_script_execute(levelScript);

    if (result.status != LEVEL_SCRIPT_SUCCESS) {
        debugf("Level script execution failed! status: %02x, index: %x\n", result.status, result.index);

        debugf("\n---- LEVEL SCRIPT DUMP ----\n");

        for (int i = 0; ; i++) {
            if (i % 16 == 0) {
                debugf("\n%04X: ", i);
            }

            debugf("%02X ", levelScript[i]);

            if (levelScript[i] == OP_LEVEL_END) {
                break;
            }
        }

        debugf("\n\n---- END OF SCRIPT DUMP ----\n");

        return;
    }

    // over means mystery dungeon (randomized levels) mode is enabled
    if (over) {
        level_shuffle();
    }

    debugf("Level loaded in %llu microseconds.\n", get_ticks_us() - time);
}
