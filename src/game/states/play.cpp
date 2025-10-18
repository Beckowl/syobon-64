#include <libdragon.h>

#include "game.hpp"
#include "play.hpp"

#include "states/credits.hpp"
#include "states/transition.hpp"

#include "ui/message_box.hpp"
#include "ui/pause_menu.hpp"

#include "sa_input.hpp"
#include "sa_audio.hpp"

#include "level/level_loader.hpp"
#include "levels.hpp"

static bool sPaused = false;

static void play_enter() {
    mainmsgtype = 0;

    ma = 5600;
    mb = 32000;
    mmuki = 1;
    mhp = 1;
    mc = 0;
    md = 0;
    mnobia = 3000;
    mnobib = 3600;

    mtype = 0;

    // チーターマン　入れ
    set_background_music(otom[1]);

    stage();
}

static bool game_can_update(void) {
    if (sPaused) {
        sPaused = pause_menu_update();
        return false;
    }

    if (is_button_pressed(BUTTON_START)) {
        sPaused = true;
        pause_menu_open();
        return false;
    }

    bool messageBoxActive = message_box_update();
    return !messageBoxActive;
}

// メインプログラム
static void play_update() {
    if (!game_can_update()) { return; }

    // プレイヤーの移動
    xx[0] = 0;
    actaon[2] = 0;
    actaon[3] = 0;
    if (mkeytm <= 0) {
        if (is_button_down(BUTTON_D_LEFT)) {
            actaon[0] = -1;
            mmuki = 0;
            actaon[4] = -1;
        }
        if (is_button_down(BUTTON_D_RIGHT)) {
            actaon[0] = 1;
            mmuki = 1;
            actaon[4] = 1;
        }
        if (is_button_down(BUTTON_D_DOWN)) {
            actaon[3] = 1;
        }
        if (is_button_down(BUTTON_A)) {
            if (actaon[1] == 10) {
                actaon[1] = 1;
                xx[0] = 1;
            }
            actaon[2] = 1;
        }
    }

    if (is_button_combo_pressed(BUTTON_L | BUTTON_R)) {
        if (mhp >= 1)
            mhp = 0;
        if (stc >= 5) {
            stc = 0;
            stagepoint = 0;
        }
    }

    if (is_button_down(BUTTON_A)) {
        if (mjumptm == 8 && md >= -900) {
            md = -1300;
            // ダッシュ中
            xx[22] = 200;
            if (mc >= xx[22] || mc <= -xx[22]) {
                md = -1400;
            }
            xx[22] = 600;
            if (mc >= xx[22] || mc <= -xx[22]) {
                md = -1500;
            }
        }

        if (xx[0] == 0)
            actaon[1] = 10;
    }

    // 加速による移動
    xx[0] = 40;
    xx[1] = 700;
    xx[8] = 500;
    xx[9] = 700;
    xx[12] = 1;
    xx[13] = 2;

    // すべり補正
    if (mrzimen == 1) {
        xx[0] = 20;
        xx[12] = 9;
        xx[13] = 10;
    }

    if (actaon[0] == -1) {
        if (!(mzimen == 0 && mc < -xx[8])) {
            if (mc >= -xx[9]) {
                mc -= xx[0];
                if (mc < -xx[9]) {
                    mc = -xx[9] - 1;
                }
            }
            if (mc < -xx[9])
                mc -= xx[0] / 10;
        }
        if (mrzimen != 1) {
            if (mc > 100 && mzimen == 0) {
                mc -= xx[0] * 2 / 3;
            }
            if (mc > 100 && mzimen == 1) {
                mc -= xx[0];
                if (mzimen == 1) {
                    mc -= xx[0] * 1 / 2;
                }
            }
            actaon[0] = 3;
            mkasok += 1;
        }
    }

    if (actaon[0] == 1) {
        if (!(mzimen == 0 && mc > xx[8])) {
            if (mc <= xx[9]) {
                mc += xx[0];
                if (mc > xx[9]) {
                    mc = xx[9] + 1;
                }
            }
            if (mc > xx[9])
                mc += xx[0] / 10;
        }
        if (mrzimen != 1) {
            if (mc < -100 && mzimen == 0) {
                mc += xx[0] * 2 / 3;
            }
            if (mc < -100 && mzimen == 1) {
                mc += xx[0];
                if (mzimen == 1) {
                    mc += xx[0] * 1 / 2;
                }
            }
            actaon[0] = 3;
            mkasok += 1;
        }
    }
    if (actaon[0] == 0 && mkasok > 0) {
        mkasok -= 2;
    }
    if (mkasok > 8) {
        mkasok = 8;
    }
    // すべり補正初期化
    if (mzimen != 1)
        mrzimen = 0;

    // ジャンプ
    if (mjumptm >= 0)
        mjumptm--;
    if (actaon[1] == 1 && mzimen == 1) {
        mb -= 400;
        md = -1200;
        mjumptm = 10;

        play_sound_effect(oto[1]);

        mzimen = 0;
    }
    if (actaon[1] <= 9)
        actaon[1] = 0;

    if (mmutekitm >= -1)
        mmutekitm--;

    // HPがなくなったとき
    if (mhp <= 0 && mhp >= -9) {
        mkeytm = 12;
        mhp = -20;
        mtype = 200;
        mtm = 0;

        stop_sound_effects();
        stop_background_music();
        play_sound_effect(oto[12]);
    }

    if (mtype == 200) {
        if (mtm <= 11) {
            mc = 0;
            md = 0;
        }
        if (mtm == 12) {
            md = -1200;
        }
        if (mtm >= 12) {
            mc = 0;
        }
        if (mtm >= 100 || fast == 1) {

            mtm = 0;
            mkeytm = 0;
            nokori--;

            play_transition(&STATE_PLAY, 30, true);
            if (fast == 1)
                mtype = 0;
        }
    }

    // 音符によるワープ
    if (mtype == 2) {
        mtm++;

        mkeytm = 2;
        md = -1500;
        if (mb <= -6000) {
            play_transition(&STATE_PLAY, 20, false);
            stc += 5;
            stop_background_music();
            mtm = 0;
            mtype = 0;
            mkeytm = -1;
        }
    }

    // ジャンプ台アウト
    if (mtype == 3) {
        md = -2400;
        if (mb <= -6000) {
            mb = -80000000;
            mhp = 0;
        }
    }
    // mtypeによる特殊的な移動
    if (mtype >= 100) {
        mtm++;

        // 普通の土管
        if (mtype == 100) {
            if (mxtype == 0) {
                mc = 0;
                md = 0;
                t = 28;
                if (mtm <= 16) {
                    mb += 240;
                    mzz = 100;
                }
                if (mtm == 17) {
                    mb = -80000000;
                }
                if (mtm == 23) {
                    sa[t] -= 100;
                }
                if (mtm >= 44 && mtm <= 60) {
                    if (mtm % 2 == 0)
                        sa[t] += 200;
                    if (mtm % 2 == 1)
                        sa[t] -= 200;
                }
                if (mtm >= 61 && mtm <= 77) {
                    if (mtm % 2 == 0)
                        sa[t] += 400;
                    if (mtm % 2 == 1)
                        sa[t] -= 400;
                }
                if (mtm >= 78 && mtm <= 78 + 16) {
                    if (mtm % 2 == 0)
                        sa[t] += 600;
                    if (mtm % 2 == 1)
                        sa[t] -= 600;
                }
                if (mtm >= 110) {
                    sb[t] -= mzz;
                    mzz += 80;
                    if (mzz > 1600)
                        mzz = 1600;
                }
                if (mtm == 160) {
                    mtype = 0;
                    mhp--;
                }
            }
            // ふっとばし
            else if (mxtype == 10) {
                mc = 0;
                md = 0;
                if (mtm <= 16) {
                    ma += 240;
                }
                if (mtm == 16)
                    mb -= 1100;
                if (mtm == 20)
                    play_sound_effect(oto[10]);

                if (mtm >= 24) {
                    ma -= 2000;
                    mmuki = 0;
                }
                if (mtm >= 48) {
                    mtype = 0;
                    mhp--;
                }
            } else {
                mc = 0;
                md = 0;
                if (mtm <= 16 && mxtype != 3) {
                    mb += 240;
                }
                if (mtm <= 16 && mxtype == 3) {
                    ma += 240;
                }
                if (mtm == 19 && mxtype == 2) {
                    mhp = 0;
                    mtype = 2000;
                    mtm = 0;
                    mmsgtm = 30;
                    mmsgtype = 51;
                }
                if (mtm == 19 && mxtype == 5) {
                    mhp = 0;
                    mtype = 2000;
                    mtm = 0;
                    mmsgtm = 30;
                    mmsgtype = 52;
                }
                if (mtm == 20) {
                    if (mxtype == 6) {
                        stc += 10;
                    } else {
                        stc++;
                    }
                    mb = -80000000;
                    mxtype = 0;
                    play_transition(&STATE_PLAY, 20, false);
                    stop_background_music();
                }
            }
        }

        if (mtype == 300) {
            mkeytm = 3;
            if (mtm <= 1) {
                mc = 0;
                md = 0;
            }
            if (mtm >= 2 && mtm <= 42) {
                md = 600;
                mmuki = 1;
            }
            if (mtm > 43 && mtm <= 108) {
                mc = 300;
            }
            if (mtm == 110) {
                mb = -80000000;
                mc = 0;
            }
            if (mtm == 250) {
                stb++;
                stc = 0;
                tyuukan = 0;
                play_transition(&STATE_PLAY, 30, true);
            }
        }

        if (mtype == 301 || mtype == 302) {
            mkeytm = 3;

            if (mtm <= 1) {
                mc = 0;
                md = 0;
            }

            if (mtm >= 2 && (mtype == 301 && mtm <= 102 || mtype == 302 && mtm <= 60)) {
                xx[5] = 500;
                ma -= xx[5];
                fx += xx[5];
            }

            if ((mtype == 301 || mtype == 302) && mtm >= 2 && mtm <= 100) {
                mc = 250;
                mmuki = 1;
            }

            if (mtm == 200) {
                play_sound_effect(oto[17]);
                if (mtype == 301) {
                    na[nco] = 117 * 29 * 100 - 1100;
                    nb[nco] = 4 * 29 * 100;
                    ntype[nco] = 101;
                    nco++;
                    if (nco >= nmax)
                        nco = 0;
                    na[nco] = 115 * 29 * 100 - 1100;
                    nb[nco] = 6 * 29 * 100;
                    ntype[nco] = 102;
                    nco++;
                    if (nco >= nmax)
                        nco = 0;
                } else {
                    na[nco] = 157 * 29 * 100 - 1100;
                    nb[nco] = 4 * 29 * 100;
                    ntype[nco] = 101;
                    nco++;
                    if (nco >= nmax)
                        nco = 0;
                    na[nco] = 155 * 29 * 100 - 1100;
                    nb[nco] = 6 * 29 * 100;
                    ntype[nco] = 102;
                    nco++;
                    if (nco >= nmax)
                        nco = 0;
                }
            }
            // スタッフロールへ

            if (mtm == 440) {
                if (mtype == 301) {
                    game_set_state(&STATE_CREDITS);
                } else {
                    sta++;
                    stb = 1;
                    stc = 0;
                    tyuukan = 0;
                    play_transition(&STATE_PLAY, 30, true);
                }
            }

        }

    }

    // 移動
    if (mkeytm >= 1) {
        mkeytm--;
    }
    ma += mc;
    mb += md;
    if (mc < 0)
        mactp += (-mc);
    if (mc >= 0)
        mactp += mc;

    if (mtype <= 9 || mtype == 200 || mtype == 300 || mtype == 301 || mtype == 302)
        md += 100;

    // 走る際の最大値
    if (mtype == 0) {
        xx[0] = 800;
        xx[1] = 1600;
        if (mc > xx[0] && mc < xx[0] + 200) {
            mc = xx[0];
        }
        if (mc > xx[0] + 200) {
            mc -= 200;
        }
        if (mc < -xx[0] && mc > -xx[0] - 200) {
            mc = -xx[0];
        }
        if (mc < -xx[0] - 200) {
            mc += 200;
        }
        if (md > xx[1]) {
            md = xx[1];
        }
    }
    // プレイヤー
    // 地面の摩擦
    if (mzimen == 1 && actaon[0] != 3) {
        if ((mtype <= 9) || mtype == 300 || mtype == 301 || mtype == 302) {
            if (mrzimen == 0) {
                xx[2] = 30;
                xx[1] = 60;
                xx[3] = 30;
                if (mc >= -xx[3] && mc <= xx[3]) {
                    mc = 0;
                }
                if (mc >= xx[2]) {
                    mc -= xx[1];
                }
                if (mc <= -xx[2]) {
                    mc += xx[1];
                }
            }
            if (mrzimen == 1) {
                xx[2] = 5;
                xx[1] = 10;
                xx[3] = 5;
                if (mc >= -xx[3] && mc <= xx[3]) {
                    mc = 0;
                }
                if (mc >= xx[2]) {
                    mc -= xx[1];
                }
                if (mc <= -xx[2]) {
                    mc += xx[1];
                }
            }
        }
    }
    // 地面判定初期化
    mzimen = 0;

    // 場外
    if (mtype <= 9 && mhp >= 1) {
        if (ma < 100) {
            ma = 100;
            mc = 0;
        }
        if (ma + mnobia > fxmax) {
            ma = fxmax - mnobia;
            mc = 0;
        }
    }

    if (mb >= 38000 && mhp >= 0 && stagecolor == 4) {
        mhp = -2;
        mmsgtm = 30;
        mmsgtype = 55;
    }
    if (mb >= 52000 && mhp >= 0) {
        mhp = -2;
    }
    // ブロック
    // 1-れんが、コイン、無し、土台、7-隠し

    xx[15] = 0;
    for (t = 0; t < tmax; t++) {
        xx[0] = 200;
        xx[1] = 3000;
        xx[2] = 1000;
        xx[3] = 3000;
        xx[8] = ta[t] - fx;
        xx[9] = tb[t] - fy;
        if (ta[t] - fx + xx[1] >= -10 - xx[3] && ta[t] - fx <= fxmax + 12000 + xx[3]) {
            if (mtype != 200 && mtype != 1 && mtype != 2) {
                if (ttype[t] < 1000 && ttype[t] != 800 && ttype[t] != 140 && ttype[t] != 141) {

                    // if (!(mztype == 1)) {
                    // mztype is never assigned to
                    if (true) {
                        xx[16] = 0;
                        xx[17] = 0;

                        // 上
                        if (ttype[t] != 7 && ttype[t] != 110 && !(ttype[t] == 114)) {
                            if (ma + mnobia > xx[8] + xx[0] * 2 + 100 && ma < xx[8] + xx[1] - xx[0] * 2 - 100 && mb + mnobib > xx[9] && mb + mnobib < xx[9] + xx[1] && md >= -100) {
                                if (ttype[t] != 115 && ttype[t] != 400 && ttype[t] != 117 && ttype[t] != 118 && ttype[t] != 120) {
                                    mb = xx[9] - mnobib + 100;
                                    md = 0;
                                    mzimen = 1;
                                    xx[16] = 1;
                                } else if (ttype[t] == 115) {
                                    brockbreak(t);
                                }
                                // Pスイッチ
                                else if (ttype[t] == 400) {
                                    md = 0;
                                    ta[t] = -8000000;
                                    play_sound_effect(oto[13]);
                                    for (tt = 0; tt < tmax; tt++) {
                                        if (ttype[tt] != 7) {
                                            ttype[tt] = 800;
                                        }
                                    }
                                    stop_background_music();
                                }
                                // 音符+
                                else if (ttype[t] == 117) {
                                    play_sound_effect(oto[14]);
                                    md = -1500;
                                    mtype = 2;
                                    mtm = 0;
                                    if (txtype[t] >= 2 && mtype == 2) {
                                        mtype = 0;
                                        md = -1600;
                                        txtype[t] = 3;
                                    }
                                    if (txtype[t] == 0)
                                        txtype[t] = 1;
                                }
                                // ジャンプ台
                                else if (ttype[t] == 120) {
                                    md = -2400;
                                    mtype = 3;
                                    mtm = 0;
                                }
                            }
                        }
                    } //!

                    // ブロック判定の入れ替え
                    //if (!(mztm >= 1 && mztype == 1)) {

                    // mztm was never assigned to (always 0) so the && was always false
                    // chiku coding ig
                    if (true) {
                        xx[21] = 0;
                        xx[22] = 1;
                        if (mzimen == 1 || mjumptm >= 10) {
                            xx[21] = 3;
                            xx[22] = 0;
                        }
                        for (t3 = 0; t3 <= 1; t3++) {

                            // 下
                            if (t3 == xx[21] && mtype != 100 && ttype[t] != 117) {
                                if (ma + mnobia > xx[8] + xx[0] * 2 + 800 && ma < xx[8] + xx[1] - xx[0] * 2 - 800 && mb > xx[9] - xx[0] * 2 && mb < xx[9] + xx[1] - xx[0] * 2 && md <= 0) {
                                    xx[16] = 1;
                                    xx[17] = 1;
                                    mb = xx[9] + xx[1] + xx[0];
                                    if (md < 0) {
                                        md = -md * 2 / 3;
                                    }
                                    // 壊れる
                                    if (ttype[t] == 1 && mzimen == 0) {
                                        brockbreak(t);
                                    }
                                    // コイン
                                    if (ttype[t] == 2 && mzimen == 0) {
                                        play_sound_effect(oto[4]);
                                        eyobi(ta[t] + 10, tb[t], 0, -800, 0, 40, 3000, 3000, 0, 16);
                                        ttype[t] = 3;
                                    }
                                    // 隠し
                                    if (ttype[t] == 7) {
                                        play_sound_effect(oto[4]);
                                        eyobi(ta[t] + 10, tb[t], 0, -800, 0, 40, 3000, 3000, 0, 16);
                                        mb = xx[9] + xx[1] + xx[0];
                                        ttype[t] = 3;
                                        if (md < 0) {
                                            md = -md * 2 / 3;
                                        }
                                    }
                                    // トゲ
                                    if (ttype[t] == 10) {
                                        mmsgtm = 30;
                                        mmsgtype = 3;
                                        mhp--;
                                    }
                                }
                            }
                            // 左右
                            if (t3 == xx[22] && xx[15] == 0) {
                                if (ttype[t] != 7 && ttype[t] != 110 && ttype[t] != 117) {
                                    if (!(ttype[t] == 114)) {
                                        if (ta[t] >= -20000) {
                                            if (ma + mnobia > xx[8] && ma < xx[8] + xx[2] && mb + mnobib > xx[9] + xx[1] / 2 - xx[0] && mb < xx[9] + xx[2] && mc >= 0) {
                                                ma = xx[8] - mnobia;
                                                mc = 0;
                                                xx[16] = 1;
                                            }
                                            if (ma + mnobia > xx[8] + xx[2] && ma < xx[8] + xx[1] && mb + mnobib > xx[9] + xx[1] / 2 - xx[0] && mb < xx[9] + xx[2] && mc <= 0) {
                                                ma = xx[8] + xx[1];
                                                mc = 0;
                                                xx[16] = 1;
                                            }
                                        }
                                    }
                                }
                            }

                        }
                    }

                }

                if (ttype[t] == 800) {
                    if (mb > xx[9] - xx[0] * 2 - 2000 && mb < xx[9] + xx[1] - xx[0] * 2 + 2000 && ma + mnobia > xx[8] - 400 && ma < xx[8] + xx[1]) {
                        ta[t] = -800000;
                        play_sound_effect(oto[4]);
                    }
                }

                // 剣とってクリア
                if (ttype[t] == 140) {
                    if (mb > xx[9] - xx[0] * 2 - 2000 && mb < xx[9] + xx[1] - xx[0] * 2 + 2000 && ma + mnobia > xx[8] - 400 && ma < xx[8] + xx[1]) {
                        ta[t] = -800000;
                        sracttype[20] = 1;
                        sron[20] = 1;
                        stop_background_music();
                        mtype = 301;
                        mtm = 0;
                        play_sound_effect(oto[16]);
                    }
                }

                // 特殊的
                if (ttype[t] == 100) {
                    if (mb > xx[9] - xx[0] * 2 - 2000 && mb < xx[9] + xx[1] - xx[0] * 2 + 2000 && ma + mnobia > xx[8] - 400 && ma < xx[8] + xx[1] && md <= 0) {
                        if (txtype[t] == 0)
                            tb[t] = mb + fy - 1200 - xx[1];
                    }

                    if (txtype[t] == 1) {
                        if (xx[17] == 1) {
                            if (ma + mnobia > xx[8] - 400 && ma < xx[8] + xx[1] / 2 - 1500) {
                                ta[t] += 3000;
                            } else if (ma + mnobia >= xx[8] + xx[1] / 2 - 1500 && ma < xx[8] + xx[1]) {
                                ta[t] -= 3000;
                            }
                        }
                    }

                    if (xx[17] == 1 && txtype[t] == 0) {
                        play_sound_effect(oto[4]);
                        eyobi(ta[t] + 10, tb[t], 0, -800, 0, 40, 3000, 3000, 0, 16);
                        ttype[t] = 3;
                    }
                }

                // 敵出現
                if (ttype[t] == 101) {
                    if (xx[17] == 1) {
                        play_sound_effect(oto[8]);
                        ttype[t] = 3;
                        abrocktm[aco] = 16;
                        if (txtype[t] == 0)
                            ayobi(ta[t], tb[t], 0, 0, 0, 0, 0);
                        if (txtype[t] == 1)
                            ayobi(ta[t], tb[t], 0, 0, 0, 4, 0);
                        if (txtype[t] == 3)
                            ayobi(ta[t], tb[t], 0, 0, 0, 101, 0);
                        if (txtype[t] == 4) {
                            abrocktm[aco] = 20;
                            ayobi(ta[t] - 400, tb[t] - 1600, 0, 0, 0, 6, 0);
                        }
                        if (txtype[t] == 10)
                            ayobi(ta[t], tb[t], 0, 0, 0, 101, 0);
                    }
                }

                // おいしいきのこ出現
                if (ttype[t] == 102) {
                    if (xx[17] == 1) {
                        play_sound_effect(oto[8]);
                        ttype[t] = 3;
                        abrocktm[aco] = 16;
                        if (txtype[t] == 0)
                            ayobi(ta[t], tb[t], 0, 0, 0, 100, 0);
                        if (txtype[t] == 2)
                            ayobi(ta[t], tb[t], 0, 0, 0, 100, 2);
                        if (txtype[t] == 3)
                            ayobi(ta[t], tb[t], 0, 0, 0, 102, 1);
                    }
                }

                // まずいきのこ出現
                if (ttype[t] == 103) {
                    if (xx[17] == 1) {
                        play_sound_effect(oto[8]);
                        ttype[t] = 3;
                        abrocktm[aco] = 16;
                        ayobi(ta[t], tb[t], 0, 0, 0, 100, 1);
                    }
                }

                // 悪スター出し
                if (ttype[t] == 104) {
                    if (xx[17] == 1) {
                        play_sound_effect(oto[8]);
                        ttype[t] = 3;
                        abrocktm[aco] = 16;
                        ayobi(ta[t], tb[t], 0, 0, 0, 110, 0);
                    }
                }

                // 毒きのこ量産
                if (ttype[t] == 110) {
                    if (xx[17] == 1) {
                        ttype[t] = 111;
                        thp[t] = 999;
                    }
                }

                if (ttype[t] == 111 && ta[t] - fx >= 0) {
                    thp[t]++;
                    if (thp[t] >= 16) {
                        thp[t] = 0;
                        play_sound_effect(oto[8]);
                        abrocktm[aco] = 16;
                        ayobi(ta[t], tb[t], 0, 0, 0, 102, 1);
                    }
                }

                // コイン量産
                if (ttype[t] == 112) {
                    if (xx[17] == 1) {
                        ttype[t] = 113;
                        thp[t] = 999;
                        titem[t] = 0;
                    }
                }

                if (ttype[t] == 113 && ta[t] - fx >= 0) {
                    if (titem[t] <= 19)
                        thp[t]++;
                    if (thp[t] >= 3) {
                        thp[t] = 0;
                        titem[t]++;
                        play_sound_effect(oto[4]);
                        eyobi(ta[t] + 10, tb[t], 0, -800, 0, 40, 3000, 3000, 0, 16);
                        // ttype[t]=3;
                    }
                }

                // 隠し毒きのこ
                if (ttype[t] == 114) {
                    if (xx[17] == 1) {
                        if (txtype[t] == 0) {
                            play_sound_effect(oto[8]);
                            ttype[t] = 3;
                            abrocktm[aco] = 16;
                            ayobi(ta[t], tb[t], 0, 0, 0, 102, 1);
                        }
                        if (txtype[t] == 2) {
                            play_sound_effect(oto[4]);
                            eyobi(ta[t] + 10, tb[t], 0, -800, 0, 40, 3000, 3000, 0, 16);
                            ttype[t] = 115;
                            txtype[t] = 0;
                        }
                        if (txtype[t] == 10) {
                            if (stageonoff == 1) {
                                ttype[t] = 130;
                                stageonoff = 0;
                                play_sound_effect(oto[13]);
                                txtype[t] = 2;
                                for (t = 0; t < amax; t++) {
                                    if (atype[t] == 87 || atype[t] == 88) {
                                        if (axtype[t] == 105) {
                                            axtype[t] = 110;
                                        }
                                    }
                                }
                            } else {
                                play_sound_effect(oto[4]);
                                eyobi(ta[t] + 10, tb[t], 0, -800, 0, 40, 3000, 3000, 0, 16);
                                ttype[t] = 3;
                            }
                        }
                    }
                }

                // もろいブロック
                if (ttype[t] == 115) {

                }

                // Pスイッチ
                if (ttype[t] == 116) {
                    if (xx[17] == 1) {
                        play_sound_effect(oto[8]);
                        ttype[t] = 3;
                        tyobi(ta[t] / 100, (tb[t] / 100) - 29, 400);
                    }
                }

                // ファイアバー強化
                if (ttype[t] == 124) {
                    if (xx[17] == 1) {
                        play_sound_effect(oto[13]);
                        for (t = 0; t < amax; t++) {
                            if (atype[t] == 87 || atype[t] == 88) {
                                if (axtype[t] == 101) {
                                    axtype[t] = 120;
                                }
                            }
                        }
                        ttype[t] = 3;
                    }
                }
                
                // ONスイッチ
                if (ttype[t] == 130) {
                    if (xx[17] == 1) {
                        if (txtype[t] != 1) {
                            stageonoff = 0;
                            play_sound_effect(oto[13]);
                        }
                    }
                } else if (ttype[t] == 131) {
                    if (xx[17] == 1 && txtype[t] != 2) {
                        stageonoff = 1;
                        play_sound_effect(oto[13]);
                        if (txtype[t] == 1) {
                            for (t = 0; t < amax; t++) {
                                if (atype[t] == 87 || atype[t] == 88) {
                                    if (axtype[t] == 105) {
                                        axtype[t] = 110;
                                    }
                                }
                            }
                            bxtype[3] = 105;
                        }
                    }
                }
                // ヒント
                if (ttype[t] == 300) {
                    if (xx[17] == 1) {
                        if (txtype[t] <= 100) {
                            message_box_open((TextMessageId)txtype[t]);
                        }
                        if (txtype[t] == 540) {
                            txtype[t] = 541;
                            message_box_open(MESSAGE_011);
                        }
                    }
                }

                if (ttype[t] == 301) {
                    if (xx[17] == 1) {
                        brockbreak(t);
                    }
                }
            } else if (mtype == 1) {
                if (ma + mnobia > xx[8] && ma < xx[8] + xx[1] && mb + mnobib > xx[9] && mb < xx[9] + xx[1]) {
                    brockbreak(t);
                }
            }
            // ONOFF
            if (ttype[t] == 130 && stageonoff == 0) {
                ttype[t] = 131;
            }
            if (ttype[t] == 131 && stageonoff == 1) {
                ttype[t] = 130;
            }
            // ヒント
            if (ttype[t] == 300) {
                if (txtype[t] >= 500 && ta[t] >= -6000) {
                    if (txtype[t] <= 539)
                        txtype[t]++;
                    if (txtype[t] >= 540) {
                        ta[t] -= 500;
                    }
                }
            }
        }
    } // ブロック

    // 壁
    for (t = 0; t < smax; t++) {
        if (sa[t] - fx + sc[t] >= -12000 && sa[t] - fx <= fxmax) {
            xx[0] = 200;
            xx[1] = 2400;
            xx[2] = 1000;
            xx[7] = 0;

            xx[8] = sa[t] - fx;
            xx[9] = sb[t] - fy;
            if ((stype[t] <= 99 || stype[t] == 200) && mtype < 10) {

                // おちるブロック
                if (stype[t] == 51) {
                    if (ma + mnobia > xx[8] + xx[0] + 3000 && ma < xx[8] + sc[t] - xx[0] && mb + mnobib > xx[9] + 3000 && sgtype[t] == 0) {
                        if (sxtype[t] == 0) {
                            sgtype[t] = 1;
                            sr[t] = 0;
                        }
                    }
                    if (ma + mnobia > xx[8] + xx[0] + 1000 && ma < xx[8] + sc[t] - xx[0] && mb + mnobib > xx[9] + 3000 && sgtype[t] == 0) {
                        if ((sxtype[t] == 10) && sgtype[t] == 0) {
                            sgtype[t] = 1;
                            sr[t] = 0;
                        }
                    }

                    if ((sxtype[t] == 1) && sb[27] >= 25000 && sa[27] > ma + mnobia && t != 27 && sgtype[t] == 0) {
                        sgtype[t] = 1;
                        sr[t] = 0;
                    }
                    if (sxtype[t] == 2 && sb[28] >= 48000 && t != 28 && sgtype[t] == 0 && mhp >= 1) {
                        sgtype[t] = 1;
                        sr[t] = 0;
                    }
                    if ((sxtype[t] == 3 && mb >= 30000 || sxtype[t] == 4 && mb >= 25000) && sgtype[t] == 0 && mhp >= 1 && ma + mnobia > xx[8] + xx[0] + 3000 - 300 && ma < xx[8] + sc[t] - xx[0]) {
                        sgtype[t] = 1;
                        sr[t] = 0;
                        if (sxtype[t] == 4)
                            sr[t] = 100;
                    }

                    if (sgtype[t] == 1 && sb[t] <= fymax + 18000) {
                        sr[t] += 120;
                        if (sr[t] >= 1600) {
                            sr[t] = 1600;
                        }
                        sb[t] += sr[t];
                        if (ma + mnobia > xx[8] + xx[0] && ma < xx[8] + sc[t] - xx[0] && mb + mnobib > xx[9] && mb < xx[9] + sd[t] + xx[0]) {
                            mhp--;
                            xx[7] = 1;
                        }
                    }
                }
                // おちるブロック2
                if (stype[t] == 52) {
                    if (sgtype[t] == 0 && ma + mnobia > xx[8] + xx[0] + 2000 && ma < xx[8] + sc[t] - xx[0] - 2500 && mb + mnobib > xx[9] - 3000) {
                        sgtype[t] = 1;
                        sr[t] = 0;
                    }
                    if (sgtype[t] == 1) {
                        sr[t] += 120;
                        if (sr[t] >= 1600) {
                            sr[t] = 1600;
                        }
                        sb[t] += sr[t];
                    }
                }
                // 通常地面
                if (xx[7] == 0) {
                    if (ma + mnobia > xx[8] + xx[0] && ma < xx[8] + sc[t] - xx[0] && mb + mnobib > xx[9] && mb + mnobib < xx[9] + xx[1] && md >= -100) {
                        mb = sb[t] - fy - mnobib + 100;
                        md = 0;
                        mzimen = 1;
                    }
                    if (ma + mnobia > xx[8] - xx[0] && ma < xx[8] + xx[2] && mb + mnobib > xx[9] + xx[1] * 3 / 4 && mb < xx[9] + sd[t] - xx[2]) {
                        ma = xx[8] - xx[0] - mnobia;
                        mc = 0;
                    }
                    if (ma + mnobia > xx[8] + sc[t] - xx[0] && ma < xx[8] + sc[t] + xx[0] && mb + mnobib > xx[9] + xx[1] * 3 / 4 && mb < xx[9] + sd[t] - xx[2]) {
                        ma = xx[8] + sc[t] + xx[0];
                        mc = 0;
                    }
                    if (ma + mnobia > xx[8] + xx[0] * 2 && ma < xx[8] + sc[t] - xx[0] * 2 && mb > xx[9] + sd[t] - xx[1] && mb < xx[9] + sd[t] + xx[0]) {
                        mb = xx[9] + sd[t] + xx[0];
                        if (md < 0) {
                            md = -md * 2 / 3;
                        }
                    }
                }

                // 入る土管
                if (stype[t] == 50) {
                    if (ma + mnobia > xx[8] + 2800 && ma < xx[8] + sc[t] - 3000 && mb + mnobib > xx[9] - 1000 && mb + mnobib < xx[9] + xx[1] + 3000 && mzimen == 1 && actaon[3] == 1 && mtype == 0) {
                        // 飛び出し
                        if (sxtype[t] == 0) {
                            mtype = 100;
                            mtm = 0;
                            play_sound_effect(oto[7]);
                            mxtype = 0;
                        }
                        // 普通
                        if (sxtype[t] == 1) {
                            mtype = 100;
                            mtm = 0;
                            play_sound_effect(oto[7]);
                            mxtype = 1;
                        }
                        // 普通
                        if (sxtype[t] == 2) {
                            mtype = 100;
                            mtm = 0;
                            play_sound_effect(oto[7]);
                            mxtype = 2;
                        }
                        if (sxtype[t] == 5) {
                            mtype = 100;
                            mtm = 0;
                            play_sound_effect(oto[7]);
                            mxtype = 5;
                        }
                        // ループ
                        if (sxtype[t] == 6) {
                            mtype = 100;
                            mtm = 0;
                            play_sound_effect(oto[7]);
                            mxtype = 6;
                        }
                    }
                }

                // 入る土管(左から)
                if (stype[t] == 40) {
                    if (ma + mnobia > xx[8] - 300 && ma < xx[8] + sc[t] - 1000 && mb > xx[9] + 1000 && mb + mnobib < xx[9] + xx[1] + 4000 && mzimen == 1 && actaon[4] == 1 && mtype == 0) { // end();
                        // 飛び出し
                        if (sxtype[t] == 0) {
                            mtype = 500;
                            mtm = 0;
                            play_sound_effect(oto[7]);
                            mtype = 100;
                            mxtype = 10;
                        }

                        if (sxtype[t] == 2) {
                            mxtype = 3;
                            mtm = 0;
                            play_sound_effect(oto[7]);
                            mtype = 100;
                        }
                        // ループ
                        if (sxtype[t] == 6) {
                            mtype = 3;
                            mtm = 0;
                            play_sound_effect(oto[7]);
                            mxtype = 6;
                        }
                    }
                }
            } else {
                if (ma + mnobia > xx[8] + xx[0] && ma < xx[8] + sc[t] - xx[0] && mb + mnobib > xx[9] && mb < xx[9] + sd[t] + xx[0]) {
                    if (stype[t] == 100) {
                        if (sxtype[t] == 0 || sxtype[t] == 1 && ttype[1] != 3) {
                            ayobi(sa[t] + 1000, 32000, 0, 0, 0, 3, 0);
                            sa[t] = -800000000;
                            play_sound_effect(oto[10]);
                        }
                    }
                    if (stype[t] == 101) {
                        ayobi(sa[t] + 6000, -4000, 0, 0, 0, 3, 1);
                        sa[t] = -800000000;
                        play_sound_effect(oto[10]);
                    }
                    if (stype[t] == 102) {
                        if (sxtype[t] == 0) {
                            for (t3 = 0; t3 <= 3; t3++) {
                                ayobi(sa[t] + t3 * 3000, -3000, 0, 0, 0, 0, 0);
                            }
                        }
                        if (sxtype[t] == 1 && mb >= 16000) {
                            ayobi(sa[t] + 1500, 44000, 0, -2000, 0, 4, 0);
                        } else if (sxtype[t] == 2) {
                            ayobi(sa[t] + 4500, 30000, 0, -1600, 0, 5, 0);
                            play_sound_effect(oto[10]);
                            sxtype[t] = 3;
                            sa[t] -= 12000;
                        } else if (sxtype[t] == 3) {
                            sa[t] += 12000;
                            sxtype[t] = 4;
                        } else if (sxtype[t] == 4) {
                            ayobi(sa[t] + 4500, 30000, 0, -1600, 0, 5, 0);
                            play_sound_effect(oto[10]);
                            sxtype[t] = 5;
                            sxtype[t] = 0;
                        } else if (sxtype[t] == 7) {
                            mainmsgtype = 1;
                        } else if (sxtype[t] == 8) {
                            ayobi(sa[t] - 5000 - 3000 * 1, 26000, 0, -1600, 0, 5, 0);
                            play_sound_effect(oto[10]);
                        } else if (sxtype[t] == 9) {
                            for (t3 = 0; t3 <= 2; t3++) {
                                ayobi(sa[t] + t3 * 3000 + 3000, 48000, 0, -6000, 0, 3, 0);
                            }
                        }
                        if (sxtype[t] == 10) {
                            sa[t] -= 5 * 30 * 100;
                            stype[t] = 101;
                        }

                        if (sxtype[t] == 12) {
                            for (t3 = 1; t3 <= 3; t3++) {
                                ayobi(sa[t] + t3 * 3000 - 1000, 40000, 0, -2600, 0, 9, 0);
                            }
                        }
                        // スクロール消し
                        if (sxtype[t] == 20) {
                            scrollx = 0;
                        }
                        // クリア
                        if (sxtype[t] == 30) {
                            sa[t] = -80000000;
                            md = 0;
                            stop_background_music();
                            mtype = 302;
                            mtm = 0;
                            play_sound_effect(oto[16]);
                        }

                        if (sxtype[t] != 3 && sxtype[t] != 4 && sxtype[t] != 10) {
                            sa[t] = -800000000;
                        }
                    }

                    if (stype[t] == 103) {
                        if (sxtype[t] == 0) {
                            amsgtm[aco] = 10;
                            amsgtype[aco] = 50;
                            ayobi(sa[t] + 9000, sb[t] + 2000, 0, 0, 0, 79, 0);
                            sa[t] = -800000000;
                        }

                        if (sxtype[t] == 1 && ttype[6] <= 6) {
                            amsgtm[aco] = 10;
                            amsgtype[aco] = 50;
                            ayobi(sa[t] - 12000, sb[t] + 2000, 0, 0, 0, 79, 0);
                            sa[t] = -800000000;
                            txtype[9] = 500;
                        }
                    } // 103

                    if (stype[t] == 104) {
                        if (sxtype[t] == 0) {
                            ayobi(sa[t] + 12000, sb[t] + 2000 + 3000, 0, 0, 0, 79, 0);
                            ayobi(sa[t] + 12000, sb[t] + 2000 + 3000, 0, 0, 0, 79, 1);
                            ayobi(sa[t] + 12000, sb[t] + 2000 + 3000, 0, 0, 0, 79, 2);
                            ayobi(sa[t] + 12000, sb[t] + 2000 + 3000, 0, 0, 0, 79, 3);
                            ayobi(sa[t] + 12000, sb[t] + 2000 + 3000, 0, 0, 0, 79, 4);
                            sa[t] = -800000000;
                        }
                    }

                    if (stype[t] == 105 && mzimen == 0 && md >= 0) {
                        ta[1] -= 1000;
                        ta[2] += 1000;
                        sxtype[t]++;
                        if (sxtype[t] >= 3)
                            sa[t] = -8000000;
                    }

                    if (stype[t] == 300 && mtype == 0 && mb < xx[9] + sd[t] + xx[0] - 3000 && mhp >= 1) {
                        stop_background_music();
                        mtype = 300;
                        mtm = 0;
                        ma = sa[t] - fx - 2000;
                        play_sound_effect(oto[11]);
                    }
                    // 中間ゲート
                    if (stype[t] == 500 && mtype == 0 && mhp >= 1) {
                        tyuukan += 1;
                        sa[t] = -80000000;
                    }
                }

                if (stype[t] == 180) {
                    sr[t]++;
                    if (sr[t] >= sgtype[t]) {
                        sr[t] = 0;
                        ayobi(sa[t], 30000, rand(600) - 300, -1600 - rand(900), 0, 84, 0);
                    }
                }
            }
        }
    } // 壁

    // キー入力初期化
    actaon[0] = 0;
    actaon[4] = 0;

    // リフト
    for (t = 0; t < srmax; t++) {
        xx[10] = sra[t];
        xx[11] = srb[t];
        xx[12] = src[t];
        xx[13] = srd[t];
        xx[8] = xx[10] - fx;
        xx[9] = xx[11] - fy;
        if (xx[8] + xx[12] >= -10 - 12000 && xx[8] <= fxmax + 12100) {
            xx[0] = 500;
            xx[1] = 1200;
            xx[2] = 1000;
            xx[7] = 2000;
            if (md >= 100) {
                xx[1] = 900 + md;
            }
            if (md > xx[1])
                xx[1] = md + 100;

            srb[t] += sre[t];
            sre[t] += srf[t];

            // 動き
            switch (sracttype[t]) {

            case 1:
                if (sron[t] == 1)
                    srf[t] = 60;
                break;

            case 2:
                break;

            case 3:
                break;

            case 5:
                if (srmove[t] == 0) {
                    srmuki[t] = 0;
                } else {
                    srmuki[t] = 1;
                }
                if (srb[t] - fy < -2100) {
                    srb[t] = fymax + fy + scrolly + 2000;
                }
                if (srb[t] - fy > fymax + scrolly + 2000) {
                    srb[t] = -2100 + fy;
                }
                break;

            case 6:
                if (sron[t] == 1)
                    srf[t] = 40;
                break;

            case 7:
                break;

            }

            // 乗ったとき
            if (mhp >= 1) {
                if (ma + mnobia > xx[8] + xx[0] && ma < xx[8] + xx[12] - xx[0] && mb + mnobib > xx[9] && mb + mnobib < xx[9] + xx[1] && md >= -100) {
                    mb = xx[9] - mnobib + 100;

                    if (srtype[t] == 1) {
                        sre[10] = 900;
                        sre[11] = 900;
                    }

                    if (srsp[t] != 12) {
                        mzimen = 1;
                        md = 0;
                    } else {
                        md = -800;
                    }

                    // 落下
                    if ((sracttype[t] == 1) && sron[t] == 0)
                        sron[t] = 1;

                    if (sracttype[t] == 1 && sron[t] == 1 || sracttype[t] == 3 || sracttype[t] == 5) {
                        mb += sre[t];
                    }

                    if (sracttype[t] == 7) {
                        if (actaon[2] != 1) {
                            md = -600;
                            mb -= 810;
                        }
                        if (actaon[2] == 1) {
                            mb -= 400;
                            md = -1400;
                            mjumptm = 10;
                        }
                    }
                    // 特殊
                    if (srsp[t] == 1) {
                        play_sound_effect(oto[3]);
                        eyobi(sra[t] + 200, srb[t] - 1000, -240, -1400, 0, 160, 4500, 4500, 2, 120);
                        eyobi(sra[t] + 4500 - 200, srb[t] - 1000, 240, -1400, 0, 160, 4500, 4500, 3, 120);
                        sra[t] = -70000000;
                    }

                    if (srsp[t] == 2) {
                        mc = -2400;
                        srmove[t] += 1;
                        if (srmove[t] >= 100) {
                            mhp = 0;
                            mmsgtype = 53;
                            mmsgtm = 30;
                            srmove[t] = -5000;
                        }
                    }

                    if (srsp[t] == 3) {
                        mc = 2400;
                        srmove[t] += 1;
                        if (srmove[t] >= 100) {
                            mhp = 0;
                            mmsgtype = 53;
                            mmsgtm = 30;
                            srmove[t] = -5000;
                        }
                    }
                } // 判定内

                // 疲れ初期化
                if ((srsp[t] == 2 || srsp[t] == 3) && mc != -2400 && srmove[t] > 0) {
                    srmove[t]--;
                }

                if (srsp[t] == 11) {
                    if (ma + mnobia > xx[8] + xx[0] - 2000 && ma < xx[8] + xx[12] - xx[0]) {
                        sron[t] = 1;
                    }
                    if (sron[t] == 1) {
                        srf[t] = 60;
                        srb[t] += sre[t];
                    }
                }
                // トゲ(下)
                if (ma + mnobia > xx[8] + xx[0] && ma < xx[8] + xx[12] - xx[0] && mb > xx[9] - xx[1] / 2 && mb < xx[9] + xx[1] / 2) {
                    if (srtype[t] == 2) {
                        if (md < 0) {
                            md = -md;
                        }
                        mb += 110;
                        if (mmutekitm <= 0)
                            mhp -= 1;
                        if (mmutekion != 1)
                            mmutekitm = 40;
                    }
                }
                // 落下
                if (sracttype[t] == 6) {
                    if (ma + mnobia > xx[8] + xx[0] && ma < xx[8] + xx[12] - xx[0]) {
                        sron[t] = 1;
                    }
                }

            }

            if (sracttype[t] == 2 || sracttype[t] == 4) {
                if (srmuki[t] == 0)
                    sra[t] -= srsok[t];
                if (srmuki[t] == 1)
                    sra[t] += srsok[t];
            }
            if (sracttype[t] == 3 || sracttype[t] == 5) {
                if (srmuki[t] == 0)
                    srb[t] -= srsok[t];
                if (srmuki[t] == 1)
                    srb[t] += srsok[t];
            }
            // 敵キャラ適用
            for (tt = 0; tt < amax; tt++) {
                if (azimentype[tt] == 1) {
                    if (aa[tt] + anobia[tt] - fx > xx[8] + xx[0] && aa[tt] - fx < xx[8] + xx[12] - xx[0] && ab[tt] + anobib[tt] > xx[11] - 100 && ab[tt] + anobib[tt] < xx[11] + xx[1] + 500 && ad[tt] >= -100) {
                        ab[tt] = xx[9] - anobib[tt] + 100;
                        ad[tt] = 0;
                        axzimen[tt] = 1;
                    }
                }
            }
        }
    } // リフト

    // グラ
    for (t = 0; t < emax; t++) {
        xx[0] = ea[t] - fx;
        xx[1] = eb[t] - fy;
        xx[2] = enobia[t] / 100;
        xx[3] = enobib[t] / 100;
        if (etm[t] >= 0)
            etm[t]--;
        if (xx[0] + xx[2] * 100 >= -10 && xx[1] <= fxmax && xx[1] + xx[3] * 100 >= -10 - 8000 && xx[3] <= fymax && etm[t] >= 0) {
            ea[t] += ec[t];
            eb[t] += ed[t];
            ec[t] += ee[t];
            ed[t] += ef[t];
        } else {
            ea[t] = -9000000;
        }

    }

    // 敵キャラの配置
    for (t = 0; t < bmax; t++) {
        if (ba[t] >= -80000) {

            if (btm[t] >= 0) {
                btm[t] = btm[t] - 1;
            }

            for (tt = 0; tt <= 1; tt++) {
                xx[0] = 0;
                xx[1] = 0;

                if (bz[t] == 0 && btm[t] < 0 && ba[t] - fx >= fxmax + 2000 && ba[t] - fx < fxmax + 2000 + mc && tt == 0) {
                    xx[0] = 1;
                    amuki[aco] = 0;
                }
                if (bz[t] == 0 && btm[t] < 0 && ba[t] - fx >= -400 - anx[btype[t]] + mc && ba[t] - fx < -400 - anx[btype[t]] && tt == 1) {
                    xx[0] = 1;
                    xx[1] = 1;
                    amuki[aco] = 1;
                }
                if (bz[t] == 1 && ba[t] - fx >= 0 - anx[btype[t]] && ba[t] - fx <= fxmax + 4000 && bb[t] - fy >= -9000 && bb[t] - fy <= fymax + 4000 && btm[t] < 0) {
                    xx[0] = 1;
                    bz[t] = 0;
                }

                if (xx[0] == 1) {
                    btm[t] = 401;
                    xx[0] = 0;
                    if (btype[t] >= 10) {
                        btm[t] = 9999999;
                    }

                    ayobi(ba[t], bb[t], 0, 0, 0, btype[t], bxtype[t]);
                }

            }
        }
    }

    // 敵キャラ
    for (t = 0; t < amax; t++) {
        xx[0] = aa[t] - fx;
        xx[1] = ab[t] - fy;
        xx[2] = anobia[t];
        xx[3] = anobib[t];
        xx[14] = 12000 * 1;
        if (anotm[t] >= 0)
            anotm[t]--;
        if (xx[0] + xx[2] >= -xx[14] && xx[0] <= fxmax + xx[14] && xx[1] + xx[3] >= -10 - 9000 && xx[1] <= fymax + 20000) {
            aacta[t] = 0;
            aactb[t] = 0;

            xx[10] = 0;

            switch (atype[t]) {
            case 0:
                xx[10] = 100;
                break;

                // こうらの敵
            case 1:
                xx[10] = 100;
                break;

                // こうら
            case 2:
                xx[10] = 0;
                xx[17] = 800;
                if (axtype[t] >= 1)
                    xx[10] = xx[17];
                // 他の敵を倒す
                if (axtype[t] >= 1) {
                    for (tt = 0; tt < amax; tt++) {
                        xx[0] = 250;
                        xx[5] = -800;
                        xx[12] = 0;
                        xx[1] = 1600;
                        xx[8] = aa[tt] - fx;
                        xx[9] = ab[tt] - fy;
                        if (t != tt) {
                            if (aa[t] + anobia[t] - fx > xx[8] + xx[0] * 2 && aa[t] - fx < xx[8] + anobia[tt] - xx[0] * 2 && ab[t] + anobib[t] - fy > xx[9] + xx[5] && ab[t] + anobib[t] - fy < xx[9] + xx[1] * 3 + xx[12] + 1500) {
                                aa[tt] = -800000;
                                play_sound_effect(oto[6]);
                            }
                        }
                    }
                }

                break;

                // あらまき
            case 3:
                azimentype[t] = 0;
                if (axtype[t] == 0) {
                    ab[t] -= 800;
                }
                if (axtype[t] == 1)
                    ab[t] += 1200;

                break;

                // スーパージエン
            case 4:
                xx[10] = 120;
                xx[0] = 250;
                xx[8] = aa[t] - fx;
                xx[9] = ab[t] - fy;
                if (atm[t] >= 0)
                    atm[t]--;
                if (abs(ma + mnobia - xx[8] - xx[0] * 2) < 9000 && abs(ma < xx[8] - anobia[t] + xx[0] * 2) < 3000 && md <= -600 && atm[t] <= 0) {
                    if (axtype[t] == 1 && mzimen == 0 && axzimen[t] == 1) {
                        ad[t] = -1600;
                        atm[t] = 40;
                        ab[t] -= 1000;
                    }
                }
                break;

                // クマー
            case 5:
                xx[10] = 160;
                break;

                // デフラグさん
            case 6:
                if (azimentype[t] == 30) {
                    ad[t] = -1600;
                    ab[t] += ad[t];
                }

                xx[10] = 120;
                if (atm[t] >= 10) {
                    atm[t]++;
                    if (mhp >= 1) {
                        if (atm[t] <= 19) {
                            ma = xx[0];
                            mb = xx[1] - 3000;
                            mtype = 0;
                        }
                        xx[10] = 0;
                        if (atm[t] == 20) {
                            mc = 700;
                            mkeytm = 24;
                            md = -1200;
                            mb = xx[1] - 1000 - 3000;
                            amuki[t] = 1;
                            if (axtype[t] == 1) {
                                mc = 840;
                                axtype[t] = 0;
                            }
                        }
                        if (atm[t] == 40) {
                            amuki[t] = 0;
                            atm[t] = 0;
                        }
                    }
                }
                // ポール捨て
                if (axtype[t] == 1) {
                    for (tt = 0; tt < smax; tt++) {
                        if (stype[tt] == 300) {
                            if (aa[t] - fx >= -8000 && aa[t] >= sa[tt] + 2000 && aa[t] <= sa[tt] + 3600 && axzimen[t] == 1) {
                                sa[tt] = -800000;
                                atm[t] = 100;
                            }
                        }
                    }

                    if (atm[t] == 100) {
                        eyobi(aa[t] + 1200 - 1200, ab[t] + 3000 - 10 * 3000 - 1500, 0, 0, 0, 0, 1000, 10 * 3000 - 1200, 4, 20);
                        if (mtype == 300) {
                            mtype = 0;
                            set_background_music(otom[1]);
                        }
                        for (t1 = 0; t1 < smax; t1++) {
                            if (stype[t1] == 104)
                                sa[t1] = -80000000;
                        }
                    }
                    if (atm[t] == 120) {
                        eyobi(aa[t] + 1200 - 1200, ab[t] + 3000 - 10 * 3000 - 1500, 600, -1200, 0, 160, 1000, 10 * 3000 - 1200, 4, 240);
                        amuki[t] = 1;
                    }
                    if (atm[t] == 140) {
                        amuki[t] = 0;
                        atm[t] = 0;
                    }
                }
                if (atm[t] >= 220) {
                    atm[t] = 0;
                    amuki[t] = 0;
                }
                // 他の敵を投げる
                for (tt = 0; tt < amax; tt++) {
                    xx[0] = 250;
                    xx[5] = -800;
                    xx[12] = 0;
                    xx[1] = 1600;
                    xx[8] = aa[tt] - fx;
                    xx[9] = ab[tt] - fy;
                    if (t != tt && atype[tt] >= 100) {
                        if (aa[t] + anobia[t] - fx > xx[8] + xx[0] * 2 && aa[t] - fx < xx[8] + anobia[tt] - xx[0] * 2 && ab[t] + anobib[t] - fy > xx[9] + xx[5] && ab[t] + anobib[t] - fy < xx[9] + xx[1] * 3 + xx[12] + 1500) {
                            amuki[tt] = 1;
                            aa[tt] = aa[t] + 300;
                            ab[tt] = ab[t] - 3000;
                            abrocktm[tt] = 120;
                            atm[t] = 200;
                            amuki[t] = 1;
                        }
                    }
                }

                break;

                // ジエン大砲
            case 7:
                azimentype[t] = 0;
                xx[10] = 0;
                xx[11] = 400;
                if (axtype[t] == 0)
                    xx[10] = xx[11];
                if (axtype[t] == 1)
                    xx[10] = -xx[11];
                if (axtype[t] == 2)
                    ab[t] -= xx[11];
                if (axtype[t] == 3)
                    ab[t] += xx[11];
                break;

                // スーパーブーン
            case 8:
                azimentype[t] = 0;
                xx[22] = 20;
                if (atm[t] == 0) {
                    af[t] += xx[22];
                    ad[t] += xx[22];
                }
                if (atm[t] == 1) {
                    af[t] -= xx[22];
                    ad[t] -= xx[22];
                }
                if (ad[t] > 300)
                    ad[t] = 300;
                if (ad[t] < -300)
                    ad[t] = -300;
                if (af[t] >= 1200)
                    atm[t] = 1;
                if (af[t] < -0)
                    atm[t] = 0;
                ab[t] += ad[t];
                // atype[t]=151;
                break;
                // ノーマルブーン
            case 151:
                azimentype[t] = 2;
                break;

                // ファイアー玉
            case 9:
                azimentype[t] = 5;
                ab[t] += ad[t];
                ad[t] += 100;
                if (ab[t] >= fymax + 1000) {
                    ad[t] = 900;
                }
                if (ab[t] >= fymax + 12000) {
                    ab[t] = fymax;
                    ad[t] = -2600;
                }
                break;

                // ファイアー
            case 10:
                azimentype[t] = 0;
                xx[10] = 0;
                xx[11] = 400;
                if (axtype[t] == 0)
                    xx[10] = xx[11];
                if (axtype[t] == 1)
                    xx[10] = -xx[11];
                break;

                // モララー
            case 30:
                atm[t] += 1;
                if (axtype[t] == 0) {
                    if (atm[t] == 50 && mb >= 6000) {
                        ac[t] = 300;
                        ad[t] -= 1600;
                        ab[t] -= 1000;
                    }

                    for (tt = 0; tt < amax; tt++) {
                        xx[0] = 250;
                        xx[5] = -800;
                        xx[12] = 0;
                        xx[1] = 1600;
                        xx[8] = aa[tt] - fx;
                        xx[9] = ab[tt] - fy;
                        if (t != tt && atype[tt] == 102) {
                            if (aa[t] + anobia[t] - fx > xx[8] + xx[0] * 2 && aa[t] - fx < xx[8] + anobia[tt] - xx[0] * 2 && ab[t] + anobib[t] - fy > xx[9] + xx[5] && ab[t] + anobib[t] - fy < xx[9] + xx[1] * 3 + xx[12] + 1500) {
                                aa[tt] = -800000;
                                axtype[t] = 1;
                                ad[t] = -1600;
                                amsgtm[t] = 30;
                                amsgtype[t] = 25;
                            }
                        }
                    }
                }
                if (axtype[t] == 1) {
                    azimentype[t] = 0;
                    ab[t] += ad[t];
                    ad[t] += 120;
                }
                break;

                // レーザー
            case 79:
                azimentype[t] = 0;
                xx[10] = 1600;
                if (axtype[t] == 1) {
                    xx[10] = 1200;
                    ab[t] -= 200;
                }
                if (axtype[t] == 2) {
                    xx[10] = 1200;
                    ab[t] += 200;
                }
                if (axtype[t] == 3) {
                    xx[10] = 900;
                    ab[t] -= 600;
                }
                if (axtype[t] == 4) {
                    xx[10] = 900;
                    ab[t] += 600;
                }
                break;

                // 雲の敵
            case 80:
                azimentype[t] = 0;
                break;
            case 81:
                azimentype[t] = 0;
                break;
            case 82:
                azimentype[t] = 0;
                break;
            case 83:
                azimentype[t] = 0;
                break;

            case 84:
                azimentype[t] = 2;
                break;

            case 85:
                xx[23] = 400;
                if (axtype[t] == 0) {
                    axtype[t] = 1;
                    amuki[t] = 1;
                }
                if (mb >= 30000 && ma >= aa[t] - 3000 * 5 - fx && ma <= aa[t] - fx && axtype[t] == 1) {
                    axtype[t] = 5;
                    amuki[t] = 0;
                }
                if (mb >= 24000 && ma <= aa[t] + 3000 * 8 - fx && ma >= aa[t] - fx && axtype[t] == 1) {
                    axtype[t] = 5;
                    amuki[t] = 1;
                }
                if (axtype[t] == 5)
                    xx[10] = xx[23];
                break;

            case 86:
                azimentype[t] = 4;
                xx[23] = 1000;
                if (ma >= aa[t] - fx - mnobia - xx[26] && ma <= aa[t] - fx + anobia[t] + xx[26]) {
                    atm[t] = 1;
                }
                if (atm[t] == 1) {
                    ab[t] += 1200;
                }
                break;

                // ファイアバー
            case 87:
                azimentype[t] = 0;
                if (aa[t] % 10 != 1)
                    atm[t] += 6;
                else {
                    atm[t] -= 6;
                }
                xx[25] = 2;
                if (atm[t] > 360 * xx[25])
                    atm[t] -= 360 * xx[25];
                if (atm[t] < 0)
                    atm[t] += 360 * xx[25];

                for (tt = 0; tt <= axtype[t] % 100; tt++) {
                    xx[26] = 18;
                    xd[4] = tt * xx[26] * cos(atm[t] * FM_PI / 180 / 2);
                    xd[5] = tt * xx[26] * sin(atm[t] * FM_PI / 180 / 2);

                    xx[4] = 1800;
                    xx[5] = 800;
                    xx[8] = aa[t] - fx + int(xd[4]) * 100 - xx[4] / 2;
                    xx[9] = ab[t] - fy + int(xd[5]) * 100 - xx[4] / 2;

                    if (ma + mnobia > xx[8] + xx[5] && ma < xx[8] + xx[4] - xx[5] && mb + mnobib > xx[9] + xx[5] && mb < xx[9] + xx[4] - xx[5]) {
                        mhp -= 1;
                        mmsgtype = 51;
                        mmsgtm = 30;
                    }
                }

                break;

            case 88:
                azimentype[t] = 0;
                if (aa[t] % 10 != 1)
                    atm[t] += 6;
                else {
                    atm[t] -= 6;
                }
                xx[25] = 2;
                if (atm[t] > 360 * xx[25])
                    atm[t] -= 360 * xx[25];
                if (atm[t] < 0)
                    atm[t] += 360 * xx[25];

                for (tt = 0; tt <= axtype[t] % 100; tt++) {
                    xx[26] = 18;
                    xd[4] = -tt * xx[26] * cos(atm[t] * FM_PI / 180 / 2);
                    xd[5] = tt * xx[26] * sin(atm[t] * FM_PI / 180 / 2);

                    xx[4] = 1800;
                    xx[5] = 800;
                    xx[8] = aa[t] - fx + int(xd[4]) * 100 - xx[4] / 2;
                    xx[9] = ab[t] - fy + int(xd[5]) * 100 - xx[4] / 2;

                    if (ma + mnobia > xx[8] + xx[5] && ma < xx[8] + xx[4] - xx[5] && mb + mnobib > xx[9] + xx[5] && mb < xx[9] + xx[4] - xx[5]) {
                        mhp -= 1;
                        mmsgtype = 51;
                        mmsgtm = 30;
                    }
                }

                break;

            case 90:
                xx[10] = 160;
                break;

                // おいしいキノコ
            case 100:
                azimentype[t] = 1;
                xx[10] = 100;

                // ほかの敵を巨大化
                if (axtype[t] == 2) {
                    for (tt = 0; tt < amax; tt++) {
                        xx[0] = 250;
                        xx[5] = -800;
                        xx[12] = 0;
                        xx[1] = 1600;
                        xx[8] = aa[tt] - fx;
                        xx[9] = ab[tt] - fy;
                        if (t != tt) {
                            if (aa[t] + anobia[t] - fx > xx[8] + xx[0] * 2 && aa[t] - fx < xx[8] + anobia[tt] - xx[0] * 2 && ab[t] + anobib[t] - fy > xx[9] + xx[5] && ab[t] + anobib[t] - fy < xx[9] + xx[1] * 3 + xx[12]) {
                                if (atype[tt] == 0 || atype[tt] == 4) {
                                    atype[tt] = 90;
                                    anobia[tt] = 6400;
                                    anobib[tt] = 6300;
                                    axtype[tt] = 0;
                                    aa[tt] -= 1050;
                                    ab[tt] -= 1050;
                                    play_sound_effect(oto[9]);
                                    aa[t] = -80000000;
                                }
                            }
                        }
                    }
                }

                break;

                // 毒キノコ
            case 102:
                azimentype[t] = 1;
                xx[10] = 100;
                if (axtype[t] == 1)
                    xx[10] = 200;
                break;

                // 悪スター
            case 110:
                azimentype[t] = 1;
                xx[10] = 200;
                if (axzimen[t] == 1) {
                    ab[t] -= 1200;
                    ad[t] = -1400;
                }
                break;

            case 200:
                azimentype[t] = 1;
                xx[10] = 100;
                break;
            }

            if (abrocktm[t] >= 1)
                xx[10] = 0;

            if (amuki[t] == 0)
                aacta[t] -= xx[10];
            if (amuki[t] == 1)
                aacta[t] += xx[10];

            // 最大値
            xx[0] = 850;
            xx[1] = 1200;

            if (ad[t] > xx[1] && azimentype[t] != 5) {
                ad[t] = xx[1];
            }
            // 行動
            aa[t] += aacta[t];

            if ((azimentype[t] >= 1 || azimentype[t] == -1) && abrocktm[t] <= 0) {

                // 移動
                aa[t] += ac[t];
                if (azimentype[t] >= 1 && azimentype[t] <= 3) {
                    ab[t] += ad[t];
                    ad[t] += 120;
                }

                if (axzimen[t] == 1) {
                    xx[0] = 100;
                    if (ac[t] >= 200) {
                        ac[t] -= xx[0];
                    } else if (ac[t] <= -200) {
                        ac[t] += xx[0];
                    } else {
                        ac[t] = 0;
                    }
                }

                axzimen[t] = 0;

                // 地面判定
                if (azimentype[t] != 2) {
                    tekizimen();
                }

            }

            // ブロックから出現するさい
            if (abrocktm[t] > 0) {
                abrocktm[t]--;
                if (abrocktm[t] < 100) {
                    ab[t] -= 180;
                }
                if (abrocktm[t] > 100) {
                }
                if (abrocktm[t] == 100) {
                    ab[t] -= 800;
                    ad[t] = -1200;
                    ac[t] = 700;
                    abrocktm[t] = 0;
                }
            }

            // プレイヤーからの判定
            xx[0] = 250;
            xx[1] = 1600;
            xx[2] = 1000;
            xx[4] = 500;
            xx[5] = -800;

            xx[8] = aa[t] - fx;
            xx[9] = ab[t] - fy;
            xx[12] = 0;
            if (md >= 100)
                xx[12] = md;
            xx[25] = 0;

            if (ma + mnobia > xx[8] + xx[0] * 2 && ma < xx[8] + anobia[t] - xx[0] * 2 && mb + mnobib > xx[9] - xx[5] && mb + mnobib < xx[9] + xx[1] + xx[12] && (mmutekitm <= 0 || md >= 100) && abrocktm[t] <= 0) {
                if (atype[t] != 4 && atype[t] != 9 && atype[t] != 10 && (atype[t] <= 78 || atype[t] == 85) && mzimen != 1 && mtype != 200) { // && atype[t]!=4 && atype[t]!=7){

                    if (atype[t] == 0) {
                        if (axtype[t] == 0)
                            aa[t] = -900000;
                        if (axtype[t] == 1) {
                            play_sound_effect(oto[5]);
                            mb = xx[9] - 900 - anobib[t];
                            md = -2100;
                            xx[25] = 1;
                            actaon[2] = 0;
                        }
                    }

                    if (atype[t] == 1) {
                        atype[t] = 2;
                        anobib[t] = 3000;
                        axtype[t] = 0;
                    }
                    // こうら
                    else if (atype[t] == 2 && md >= 0) {
                        if (axtype[t] == 1 || axtype[t] == 2) {
                            axtype[t] = 0;
                        } else if (axtype[t] == 0) {
                            if (ma + mnobia > xx[8] + xx[0] * 2 && ma < xx[8] + anobia[t] / 2 - xx[0] * 4) {
                                axtype[t] = 1;
                                amuki[t] = 1;
                            } else {
                                axtype[t] = 1;
                                amuki[t] = 0;
                            }
                        }
                    }
                    if (atype[t] == 3) {
                        xx[25] = 1;
                    }

                    if (atype[t] == 6) {
                        atm[t] = 10;
                        md = 0;
                        actaon[2] = 0;
                    }

                    if (atype[t] == 7) {
                        aa[t] = -900000;
                    }

                    if (atype[t] == 8) {
                        atype[t] = 151;
                        ad[t] = 0;
                    }

                    if (atype[t] != 85) {
                        if (xx[25] == 0) {
                            play_sound_effect(oto[5]);
                            mb = xx[9] - 1000 - anobib[t];
                            md = -1000;
                        }
                    }
                    if (atype[t] == 85) {
                        if (xx[25] == 0) {
                            play_sound_effect(oto[5]);
                            mb = xx[9] - 4000;
                            md = -1000;
                            axtype[t] = 5;
                        }
                    }

                    if (actaon[2] == 1) {
                        md = -1600;
                        actaon[2] = 0;
                    }
                }
            }

            xx[15] = -500;

            // プレイヤーに触れた時
            xx[16] = 0;
            if (atype[t] == 4 || atype[t] == 9 || atype[t] == 10)
                xx[16] = -3000;
            if (atype[t] == 82 || atype[t] == 83 || atype[t] == 84)
                xx[16] = -3200;
            if (atype[t] == 85)
                xx[16] = -anobib[t] + 6000;
            if (ma + mnobia > xx[8] + xx[4] && ma < xx[8] + anobia[t] - xx[4] && mb < xx[9] + anobib[t] + xx[15] && mb + mnobib > xx[9] + anobib[t] - xx[0] + xx[16] && anotm[t] <= 0 && abrocktm[t] <= 0) {
                if (mmutekion == 1) {
                    aa[t] = -9000000;
                }
                if (mmutekitm <= 0 && (atype[t] <= 99 || atype[t] >= 200)) {
                    if (mmutekion != 1 && mtype != 200) {

                        // ダメージ
                        if ((atype[t] != 2 || axtype[t] != 0) && mhp >= 1) {
                            if (atype[t] != 6) {
                                mhp -= 1;
                            }
                        }

                        if (atype[t] == 6) {
                            atm[t] = 10;
                        }
                        // せりふ
                        if (mhp == 0) {

                            if (atype[t] == 0 || atype[t] == 7) {
                                amsgtm[t] = 60;
                                amsgtype[t] = rand(7) + 1 + 1000 + (stb - 1) * 10;
                            }

                            if (atype[t] == 1) {
                                amsgtm[t] = 60;
                                amsgtype[t] = rand(2) + 15;
                            }

                            if (atype[t] == 2 && axtype[t] >= 1 && mmutekitm <= 0) {
                                amsgtm[t] = 60;
                                amsgtype[t] = 18;
                            }

                            if (atype[t] == 3) {
                                amsgtm[t] = 60;
                                amsgtype[t] = 20;
                            }

                            if (atype[t] == 4) {
                                amsgtm[t] = 60;
                                amsgtype[t] = rand(7) + 1 + 1000 + (stb - 1) * 10;
                            }

                            if (atype[t] == 5) {
                                amsgtm[t] = 60;
                                amsgtype[t] = 21;
                            }

                            if (atype[t] == 9 || atype[t] == 10) {
                                mmsgtm = 30;
                                mmsgtype = 54;
                            }

                            if (atype[t] == 31) {
                                amsgtm[t] = 30;
                                amsgtype[t] = 24;
                            }

                            if (atype[t] == 80 || atype[t] == 81) {
                                amsgtm[t] = 60;
                                amsgtype[t] = 30;
                            }

                            if (atype[t] == 82) {
                                amsgtm[t] = 20;
                                amsgtype[t] = rand(1) + 31;
                                xx[24] = 900;
                                atype[t] = 83;
                                aa[t] -= xx[24] + 100;
                                ab[t] -= xx[24] - 100 * 0;
                            }

                            if (atype[t] == 84) {
                                mmsgtm = 30;
                                mmsgtype = 50;
                            }

                            if (atype[t] == 85) {
                                amsgtm[t] = 60;
                                amsgtype[t] = rand(1) + 85;
                            }
                            // 雲
                            if (atype[t] == 80) {
                                atype[t] = 81;
                            }

                        }

                        // こうら
                        if (atype[t] == 2) {
                            if (axtype[t] == 0) {
                                if (ma + mnobia > xx[8] + xx[0] * 2 && ma < xx[8] + anobia[t] / 2 - xx[0] * 4) {
                                    axtype[t] = 1;
                                    amuki[t] = 1;
                                    aa[t] = ma + mnobia + fx + mc;
                                    mmutekitm = 5;
                                } else {
                                    axtype[t] = 1;
                                    amuki[t] = 0;
                                    aa[t] = ma - anobia[t] + fx - mc;
                                    mmutekitm = 5;
                                }
                            } else {
                                mhp -= 1;
                            }
                        }
                    }
                }
                // アイテム
                if (atype[t] >= 100 && atype[t] <= 199) {

                    if (atype[t] == 100 && axtype[t] == 0) {
                        mmsgtm = 30;
                        mmsgtype = 1;
                        play_sound_effect(oto[9]);
                    }
                    if (atype[t] == 100 && axtype[t] == 1) {
                        mmsgtm = 30;
                        mmsgtype = 2;
                        play_sound_effect(oto[9]);
                    }
                    if (atype[t] == 100 && axtype[t] == 2) {
                        mnobia = 5200;
                        mnobib = 7300;
                        play_sound_effect(oto[9]);
                        ma -= 1100;
                        mb -= 4000;
                        mtype = 1;
                        mhp = 50000000;
                    }

                    if (atype[t] == 101) {
                        mhp -= 1;
                        mmsgtm = 30;
                        mmsgtype = 11;
                    }
                    if (atype[t] == 102) {
                        mhp -= 1;
                        mmsgtm = 30;
                        mmsgtype = 10;
                    }
                    //?ボール
                    if (atype[t] == 105) {
                        if (axtype[t] == 0) {
                            play_sound_effect(oto[4]);
                            sgtype[26] = 6;
                        }
                        if (axtype[t] == 1) {
                            txtype[7] = 80;
                            play_sound_effect(oto[4]);

                            ayobi(aa[t] - 8 * 3000 - 1000, -4 * 3000, 0, 0, 0, 110, 0);
                            ayobi(aa[t] - 10 * 3000 + 1000, -1 * 3000, 0, 0, 0, 110, 0);

                            ayobi(aa[t] + 4 * 3000 + 1000, -2 * 3000, 0, 0, 0, 110, 0);
                            ayobi(aa[t] + 5 * 3000 - 1000, -3 * 3000, 0, 0, 0, 110, 0);
                            ayobi(aa[t] + 6 * 3000 + 1000, -4 * 3000, 0, 0, 0, 110, 0);
                            ayobi(aa[t] + 7 * 3000 - 1000, -2 * 3000, 0, 0, 0, 110, 0);
                            ayobi(aa[t] + 8 * 3000 + 1000, -2 * 3000 - 1000, 0, 0, 0, 110, 0);
                            tb[0] += 3000 * 3;
                        }
                    } // 105

                    if (atype[t] == 110) {
                        mhp -= 1;
                        mmsgtm = 30;
                        mmsgtype = 3;
                    }

                    aa[t] = -90000000;
                }

            }
        } else {
            aa[t] = -9000000;
        }

    }

    // スクロール
    if (true) {
        xx[2] = mascrollmax;
        xx[3] = 0;
        xx[1] = xx[2];
        if (ma > xx[1] && fx < scrollx) {
            xx[5] = ma - xx[1];
            ma = xx[1];
            fx += xx[5];
            if (xx[1] <= 5000)
                xx[3] = 1;
        }
    }
}

void tekizimen() {

    // 壁
    for (tt = 0; tt < smax; tt++) {
        if (sa[tt] - fx + sc[tt] >= -12010 && sa[tt] - fx <= fxmax + 12100 && stype[tt] <= 99) {
            xx[0] = 200;
            xx[2] = 1000;
            xx[1] = 2000;

            xx[8] = sa[tt] - fx;
            xx[9] = sb[tt] - fy;
            if (aa[t] + anobia[t] - fx > xx[8] - xx[0] && aa[t] - fx < xx[8] + xx[2] && ab[t] + anobib[t] - fy > xx[9] + xx[1] * 3 / 4 && ab[t] - fy < xx[9] + sd[tt] - xx[2]) {
                aa[t] = xx[8] - xx[0] - anobia[t] + fx;
                amuki[t] = 0;
            }
            if (aa[t] + anobia[t] - fx > xx[8] + sc[tt] - xx[0] && aa[t] - fx < xx[8] + sc[tt] + xx[0] && ab[t] + anobib[t] - fy > xx[9] + xx[1] * 3 / 4 && ab[t] - fy < xx[9] + sd[tt] - xx[2]) {
                aa[t] = xx[8] + sc[tt] + xx[0] + fx;
                amuki[t] = 1;
            }
            
            if (aa[t] + anobia[t] - fx > xx[8] + xx[0] && aa[t] - fx < xx[8] + sc[tt] - xx[0] && ab[t] + anobib[t] - fy > xx[9] && ab[t] + anobib[t] - fy < xx[9] + sd[tt] - xx[1] && ad[t] >= -100) {
                ab[t] = sb[tt] - fy - anobib[t] + 100 + fy;
                ad[t] = 0;
                axzimen[t] = 1;
            }

            if (aa[t] + anobia[t] - fx > xx[8] + xx[0] && aa[t] - fx < xx[8] + sc[tt] - xx[0] && ab[t] - fy > xx[9] + sd[tt] - xx[1] && ab[t] - fy < xx[9] + sd[tt] + xx[0]) {
                ab[t] = xx[9] + sd[tt] + xx[0] + fy;
                if (ad[t] < 0) {
                    ad[t] = -ad[t] * 2 / 3;
                }
            }
        }
    }

    // ブロック
    for (tt = 0; tt < tmax; tt++) {
        xx[0] = 200;
        xx[1] = 3000;
        xx[2] = 1000;
        xx[8] = ta[tt] - fx;
        xx[9] = tb[tt] - fy;
        if (ta[tt] - fx + xx[1] >= -12010 && ta[tt] - fx <= fxmax + 12000) {
            if (atype[t] != 86 && atype[t] != 90 && ttype[tt] != 140) {

                // 上
                if (ttype[tt] != 7) {
                    if (!(ttype[tt] == 117)) {
                        if (aa[t] + anobia[t] - fx > xx[8] + xx[0] && aa[t] - fx < xx[8] + xx[1] - xx[0] * 1 && ab[t] + anobib[t] - fy > xx[9] && ab[t] + anobib[t] - fy < xx[9] + xx[1] && ad[t] >= -100) {
                            ab[t] = xx[9] - anobib[t] + 100 + fy;
                            ad[t] = 0;
                            axzimen[t] = 1;
                            // ジャンプ台
                            if (ttype[tt] == 120) {
                                ad[t] = -1600;
                                azimentype[t] = 30;
                            }
                        }
                    }
                }
                // 下
                if (ttype[tt] != 117) {
                    if (aa[t] + anobia[t] - fx > xx[8] + xx[0] && aa[t] - fx < xx[8] + xx[1] - xx[0] * 1 && ab[t] - fy > xx[9] + xx[1] - xx[1] && ab[t] - fy < xx[9] + xx[1] + xx[0]) {
                        ab[t] = xx[9] + xx[1] + xx[0] + fy;
                        if (ad[t] < 0) {
                            ad[t] = 0;
                        }
                    }
                }
                // 左右
                xx[27] = 0;
                if ((atype[t] >= 100 || (ttype[tt] != 7 || ttype[tt] == 7 && atype[t] == 2)) && ttype[tt] != 117) {
                    if (aa[t] + anobia[t] - fx > xx[8] && aa[t] - fx < xx[8] + xx[2] && ab[t] + anobib[t] - fy > xx[9] + xx[1] / 2 - xx[0] && ab[t] - fy < xx[9] + xx[2]) {
                        aa[t] = xx[8] - anobia[t] + fx;
                        ac[t] = 0;
                        amuki[t] = 0;
                        xx[27] = 1;
                    }
                    if (aa[t] + anobia[t] - fx > xx[8] + xx[1] - xx[0] * 2 && aa[t] - fx < xx[8] + xx[1] && ab[t] + anobib[t] - fy > xx[9] + xx[1] / 2 - xx[0] && ab[t] - fy < xx[9] + xx[2]) {
                        aa[t] = xx[8] + xx[1] + fx;
                        ac[t] = 0;
                        amuki[t] = 1;
                        xx[27] = 1;
                    }
                    // こうらブレイク
                    if (xx[27] == 1 && (ttype[tt] == 7 || ttype[tt] == 1) && atype[t] == 2) {
                        if (ttype[tt] == 7) {
                            play_sound_effect(oto[4]);
                            ttype[tt] = 3;
                            eyobi(ta[tt] + 10, tb[tt], 0, -800, 0, 40, 3000, 3000, 0, 16);
                        } else if (ttype[tt] == 1) {
                            brockbreak(tt);
                        }
                    }
                }
            }
            if (atype[t] == 86 || atype[t] == 90) {
                if (aa[t] + anobia[t] - fx > xx[8] && aa[t] - fx < xx[8] + xx[1] && ab[t] + anobib[t] - fy > xx[9] && ab[t] - fy < xx[9] + xx[1]) {
                    brockbreak(tt);
                }
            }
        }
        // 剣とってクリア
        if (ttype[tt] == 140) {
            if (ab[t] - fy > xx[9] - xx[0] * 2 - 2000 && ab[t] - fy < xx[9] + xx[1] - xx[0] * 2 + 2000 && aa[t] + anobia[t] - fx > xx[8] - 400 && aa[t] - fx < xx[8] + xx[1]) {
                ta[tt] = -800000;
                sracttype[20] = 1;
                sron[20] = 1;
            }
        }
    } // tt

} // tekizimen

// moves player to the checkpoint that
// corresponds to the checkpoint index (tyuukan)
void player_init_checkpoint(void) {
    if (tyuukan >= 1) {
        xx[17] = 0;
        for (t = 0; t < smax; t++) {
            if (stype[t] == 500 && tyuukan >= 1) {
                fx = sa[t] - fxmax / 2;
                ma = sa[t] - fx;
                mb = sb[t] - fy;
                tyuukan--;
                xx[17]++;

                sa[t] = -80000000;
            }
        }
        tyuukan += xx[17];
    }
}

//ステージロード
void stage() {
    // 1-レンガ,2-コイン,3-空,4-土台//5-6地面//7-隠し//
    stagep();

    for (tt = 0; tt <= 1000; tt++) {
        for (t = 0; t <= 16; t++) {
            xx[10] = 0;

            if (stagedate[t][tt] >= 1 && stagedate[t][tt] <= 255)
                xx[10] = (int)stagedate[t][tt];

            xx[21] = tt * 29;
            xx[22] = t * 29 - 12;
            xx[23] = xx[10];

            if (xx[10] >= 1 && xx[10] <= 19 && xx[10] != 9) {
                tyobi(tt * 29, t * 29 - 12, xx[10]);
            }

            if (xx[10] >= 20 && xx[10] <= 29) {
                sra[srco] = xx[21] * 100;
                srb[srco] = xx[22] * 100;
                src[srco] = 3000;
                srtype[srco] = 0;
                srco++;

                if (srco >= srmax)
                    srco = 0;
            }

            if (xx[10] == 30) {
                sa[sco] = xx[21] * 100;
                sb[sco] = xx[22] * 100;
                sc[sco] = 3000;
                sd[sco] = 6000;
                stype[sco] = 500;
                sco++;
                if (sco >= smax)
                    sco = 0;
            }

            if (xx[10] == 40) {
                sa[sco] = xx[21] * 100;
                sb[sco] = xx[22] * 100;
                sc[sco] = 6000;
                sd[sco] = 3000;
                stype[sco] = 1;
                sco++;
                if (sco >= smax)
                    sco = 0;
            }

            if (xx[10] == 41) {
                sa[sco] = xx[21] * 100 + 500;
                sb[sco] = xx[22] * 100;
                sc[sco] = 5000;
                sd[sco] = 3000;
                stype[sco] = 2;
                sco++;
                if (sco >= smax)
                    sco = 0;
            }

            if (xx[10] == 43) {
                sa[sco] = xx[21] * 100;
                sb[sco] = xx[22] * 100 + 500;
                sc[sco] = 2900;
                sd[sco] = 5300;
                stype[sco] = 1;
                sco++;
                if (sco >= smax)
                    sco = 0;
            }

            if (xx[10] == 44) {
                sa[sco] = xx[21] * 100;
                sb[sco] = xx[22] * 100 + 700;
                sc[sco] = 3900;
                sd[sco] = 5000;
                stype[sco] = 5;
                sco++;
                if (sco >= smax)
                    sco = 0;
            }

            // これなぜかバグの原因ｗ
            if (xx[10] >= 50 && xx[10] <= 79) {
                ba[bco] = xx[21] * 100;
                bb[bco] = xx[22] * 100;
                btype[bco] = xx[23] - 50;
                bco++;
                if (bco >= bmax)
                    bco = 0;
            }

            if (xx[10] >= 80 && xx[10] <= 89)
            {
                na[nco] = xx[21] * 100;
                nb[nco] = xx[22] * 100;
                ntype[nco] = xx[23] - 80;
                nco++;
                if (nco >= nmax)
                    nco = 0;
            }

            // コイン
            if (xx[10] == 9) {
                tyobi(tt * 29, t * 29 - 12, 800);
            }
            if (xx[10] == 99) {
                sa[sco] = xx[21] * 100;
                sb[sco] = xx[22] * 100;
                sc[sco] = 3000;
                sd[sco] = (12 - t) * 3000;
                stype[sco] = 300;
                sco++;
                if (sco >= smax)
                    sco = 0;
            }
        }
    }

    // TODO: remove this when you convert all levels to level scripts
    if (over == 1) {
        level_randomize();
    }

    player_init_checkpoint();
}

// メイン描画
static void play_draw() {

    // ダブルバッファリング
    set_draw_color(0, 0, 0);

    if (stagecolor == 1)
        set_draw_color(160, 180, 250);
    if (stagecolor == 2)
        set_draw_color(10, 10, 10);
    if (stagecolor == 3)
        set_draw_color(160, 180, 250);
    if (stagecolor == 4)
        set_draw_color(10, 10, 10);
    if (stagecolor == 5) {
        set_draw_color(160, 180, 250);
        mrzimen = 1;
    } else {
        mrzimen = 0;
    }

    sa_graphics_clear();

    // 背景
    for (t = 0; t < nmax; t++) {
        xx[0] = na[t] - fx;
        xx[1] = nb[t] - fy;
        xx[2] = ne[ntype[t]] * 100;
        xx[3] = nf[ntype[t]] * 100;
        xx[2] = 16000;
        xx[3] = 16000;

        if (xx[0] + xx[2] >= -10 && xx[0] <= fxmax && xx[1] + xx[3] >= -10 && xx[3] <= fymax) {

            if (ntype[t] != 3) {
                if ((ntype[t] == 1 || ntype[t] == 2) && stagecolor == 5) {
                    draw_sprite_region(grap[ntype[t] + 30][4], xx[0] / 100, xx[1] / 100, mirror);
                } else {
                    draw_sprite_region(grap[ntype[t]][4], xx[0] / 100, xx[1] / 100, mirror);
                }
            }
            if (ntype[t] == 3)
                draw_sprite_region(grap[ntype[t]][4], xx[0] / 100 - 5, xx[1] / 100, mirror);

            // 51
            if (ntype[t] == 100) {
                draw_text("51", xx[0] / 100, xx[1] / 100);
            }

            if (ntype[t] == 101)
                draw_text("ゲームクリアー", xx[0] / 100, xx[1] / 100);
            if (ntype[t] == 102)
                draw_text("プレイしてくれてありがとー", xx[0] / 100, xx[1] / 100);
        }
    }

    // グラ
    for (t = 0; t < emax; t++) {
        xx[0] = ea[t] - fx;
        xx[1] = eb[t] - fy;
        xx[2] = enobia[t] / 100;
        xx[3] = enobib[t] / 100;
        if (xx[0] + xx[2] * 100 >= -10 && xx[1] <= fxmax && xx[1] + xx[3] * 100 >= -10 - 8000 && xx[3] <= fymax) {

            // コイン
            if (egtype[t] == 0)
                draw_sprite_region(grap[0][2], xx[0] / 100, xx[1] / 100, mirror);

            // ブロックの破片
            if (egtype[t] == 1) {
                rdpq_set_mode_standard();
                rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);
                rdpq_mode_alphacompare(1);

                if (stagecolor == 1 || stagecolor == 3 || stagecolor == 5)
                    rdpq_set_prim_color(RGBA32(9 * 16, 6 * 16, 3 * 16, 255));
                if (stagecolor == 2)
                    rdpq_set_prim_color(RGBA32(0, 120, 160, 255));
                if (stagecolor == 4)
                    rdpq_set_prim_color(RGBA32(192, 192, 192, 255));

                rdpq_sprite_blit(mgrap[8], xx[0] / 100, xx[1] / 100, NULL);
                rdpq_set_prim_color(RGBA32(255, 255, 255, 255));
            }
            // リフトの破片
            if (egtype[t] == 2 || egtype[t] == 3) {
                if (egtype[t] == 3)
                    mirror = 1;
                draw_sprite_region(grap[0][5], xx[0] / 100, xx[1] / 100, mirror);
                mirror = 0;
            }
            // ポール
            if (egtype[t] == 4) {
                set_draw_color(255, 255, 255);

                draw_rectangle_filled((xx[0]) / 100 + 10, (xx[1]) / 100, 10, xx[3]);
                set_draw_color(0, 0, 0);

                draw_rectangle_outline((xx[0]) / 100 + 10, (xx[1]) / 100, 10, xx[3]);
                set_draw_color(250, 250, 0);
                draw_circle_filled((xx[0]) / 100 + 15 - 1, (xx[1]) / 100, 10);
                set_draw_color(0, 0, 0);

                draw_circle_outline((xx[0]) / 100 + 15 - 1, (xx[1]) / 100, 10);
            }
        }
    }

    // リフト
    for (t = 0; t < srmax; t++) {
        xx[0] = sra[t] - fx;
        xx[1] = srb[t] - fy;
        if (xx[0] + src[t] >= -10 && xx[1] <= fxmax + 12100 && src[t] / 100 >= 1) {
            xx[2] = 14;
            if (srsp[t] == 1) {
                xx[2] = 12;
            }

            if (srsp[t] <= 9 || srsp[t] >= 20) {
                set_draw_color(220, 220, 0);
                if (srsp[t] == 2 || srsp[t] == 3) {
                    set_draw_color(0, 220, 0);
                }
                if (srsp[t] == 21) {
                    set_draw_color(180, 180, 180);
                }
                draw_rectangle_filled((sra[t] - fx) / 100, (srb[t] - fy) / 100, src[t] / 100, xx[2]);

                set_draw_color(180, 180, 0);
                if (srsp[t] == 2 || srsp[t] == 3) {
                    set_draw_color(0, 180, 0);
                }
                if (srsp[t] == 21) {
                    set_draw_color(150, 150, 150);
                }
                draw_rectangle_outline((sra[t] - fx) / 100, (srb[t] - fy) / 100, src[t] / 100, xx[2]);
            } else if (srsp[t] <= 14) {
                if (src[t] >= 5000) {
                    set_draw_color(0, 200, 0);
                    draw_rectangle_filled((sra[t] - fx) / 100, (srb[t] - fy) / 100, src[t] / 100, 30);
                    set_draw_color(0, 160, 0);
                    draw_rectangle_outline((sra[t] - fx) / 100, (srb[t] - fy) / 100, src[t] / 100, 30);

                    set_draw_color(180, 120, 60);
                    draw_rectangle_filled((sra[t] - fx) / 100 + 20, (srb[t] - fy) / 100 + 30, src[t] / 100 - 40, 480);
                    set_draw_color(100, 80, 20);
                    draw_rectangle_outline((sra[t] - fx) / 100 + 20, (srb[t] - fy) / 100 + 30, src[t] / 100 - 40, 480);
                }
            }
            if (srsp[t] == 15) {
                for (t2 = 0; t2 <= 2; t2++) {
                    xx[6] = 1 + 0;
                    draw_sprite_region(grap[xx[6]][1], (sra[t] - fx) / 100 + t2 * 29, (srb[t] - fy) / 100, mirror);
                }
            }
        }
    }

    // プレイヤー描画
    set_draw_color(0, 0, 255);

    if (mactp >= 2000) {
        mactp -= 2000;
        if (mact == 0) {
            mact = 1;
        } else {
            mact = 0;
        }
    }
    if (mmuki == 0)
        mirror = 1;

    if (mtype != 200 && mtype != 1) {
        if (mzimen == 1) {
            // 読みこんだグラフィックを拡大描画
            if (mact == 0)
                draw_sprite_region(grap[0][0], ma / 100, mb / 100, mirror);
            if (mact == 1)
                draw_sprite_region(grap[1][0], ma / 100, mb / 100, mirror);
        }
        if (mzimen == 0) {
            draw_sprite_region(grap[2][0], ma / 100, mb / 100, mirror);
        }
    }
    // 巨大化
    else if (mtype == 1) {
        draw_sprite_region(grap[41][0], ma / 100, mb / 100, mirror);
    } else if (mtype == 200) {
        draw_sprite_region(grap[3][0], ma / 100, mb / 100, mirror);
    }

    mirror = 0;

    // 敵キャラ
    for (t = 0; t < amax; t++) {

        xx[0] = aa[t] - fx;
        xx[1] = ab[t] - fy;
        xx[2] = anobia[t] / 100;
        xx[3] = anobib[t] / 100;
        xx[14] = 3000;
        xx[16] = 0;
        if (xx[0] + xx[2] * 100 >= -10 - xx[14] && xx[1] <= fxmax + xx[14] && xx[1] + xx[3] * 100 >= -10 && xx[3] <= fymax) {
            if (amuki[t] == 1) {
                mirror = 1;
            }
            if (atype[t] == 3 && axtype[t] == 1) {
                draw_sprite_region(grap[atype[t]][3], xx[0] / 100, xx[1] / 100, false, true);
                xx[16] = 1;
            }
            if (atype[t] == 9 && ad[t] >= 1) {
                draw_sprite_region(grap[atype[t]][3], xx[0] / 100, xx[1] / 100, false, true);
                xx[16] = 1;
            }
            if (atype[t] >= 100 && amuki[t] == 1)
                mirror = 0;

            // メイン
            if (atype[t] < 200 && xx[16] == 0 && atype[t] != 6 && atype[t] != 79 && atype[t] != 86 && atype[t] != 30) {
                if (!((atype[t] == 80 || atype[t] == 81) && axtype[t] == 1)) {
                    draw_sprite_region(grap[atype[t]][3], xx[0] / 100, xx[1] / 100, mirror);
                }
            }
            // デフラグさん
            if (atype[t] == 6) {
                if (atm[t] >= 10 && atm[t] <= 19 || atm[t] >= 100 && atm[t] <= 119 || atm[t] >= 200) {
                    draw_sprite_region(grap[150][3], xx[0] / 100, xx[1] / 100, mirror);
                } else {
                    draw_sprite_region(grap[6][3], xx[0] / 100, xx[1] / 100, mirror);
                }
            }
            // モララー
            if (atype[t] == 30) {
                if (axtype[t] == 0)
                    draw_sprite_region(grap[30][3], xx[0] / 100, xx[1] / 100, mirror);
                if (axtype[t] == 1)
                    draw_sprite_region(grap[155][3], xx[0] / 100, xx[1] / 100, mirror);
            }
            // ステルス雲
            if ((atype[t] == 81) && axtype[t] == 1) {
                draw_sprite_region(grap[130][3], xx[0] / 100, xx[1] / 100, mirror);
            }

            if (atype[t] == 79) {
                set_draw_color(250, 250, 0);
                draw_rectangle_filled(xx[0] / 100, xx[1] / 100, xx[2], xx[3]);
                set_draw_color(0, 0, 0);

                draw_rectangle_outline(xx[0] / 100, xx[1] / 100, xx[2], xx[3]);
            }

            if (atype[t] == 82) {

                if (axtype[t] == 0) {
                    xx[9] = 0;
                    if (stagecolor == 2) {
                        xx[9] = 30;
                    }
                    if (stagecolor == 4) {
                        xx[9] = 60;
                    }
                    if (stagecolor == 5) {
                        xx[9] = 90;
                    }
                    xx[6] = 5 + xx[9];
                    draw_sprite_region(grap[xx[6]][1], xx[0] / 100, xx[1] / 100, mirror);
                }

                if (axtype[t] == 1) {
                    xx[9] = 0;
                    if (stagecolor == 2) {
                        xx[9] = 30;
                    }
                    if (stagecolor == 4) {
                        xx[9] = 60;
                    }
                    if (stagecolor == 5) {
                        xx[9] = 90;
                    }
                    xx[6] = 4 + xx[9];
                    draw_sprite_region(grap[xx[6]][1], xx[0] / 100, xx[1] / 100, mirror);
                }

                if (axtype[t] == 2) {
                    draw_sprite_region(grap[1][5], xx[0] / 100, xx[1] / 100, mirror);
                }
            }
            if (atype[t] == 83) {

                if (axtype[t] == 0) {
                    xx[9] = 0;
                    if (stagecolor == 2) {
                        xx[9] = 30;
                    }
                    if (stagecolor == 4) {
                        xx[9] = 60;
                    }
                    if (stagecolor == 5) {
                        xx[9] = 90;
                    }
                    xx[6] = 5 + xx[9];
                    draw_sprite_region(grap[xx[6]][1], xx[0] / 100 + 10, xx[1] / 100 + 9, mirror);
                }

                if (axtype[t] == 1) {
                    xx[9] = 0;
                    if (stagecolor == 2) {
                        xx[9] = 30;
                    }
                    if (stagecolor == 4) {
                        xx[9] = 60;
                    }
                    if (stagecolor == 5) {
                        xx[9] = 90;
                    }
                    xx[6] = 4 + xx[9];
                    draw_sprite_region(grap[xx[6]][1], xx[0] / 100 + 10, xx[1] / 100 + 9, mirror);
                }
            }
            // 偽ポール
            if (atype[t] == 85) {
                set_draw_color(255, 255, 255);

                draw_rectangle_filled((xx[0]) / 100 + 10, (xx[1]) / 100, 10, xx[3]);
                set_draw_color(0, 0, 0);

                draw_rectangle_outline((xx[0]) / 100 + 10, (xx[1]) / 100, 10, xx[3]);
                set_draw_color(0, 250, 200);
                draw_circle_filled((xx[0]) / 100 + 15 - 1, (xx[1]) / 100, 10);
                set_draw_color(0, 0, 0);

                draw_circle_outline((xx[0]) / 100 + 15 - 1, (xx[1]) / 100, 10);

            }

            // ニャッスン
            if (atype[t] == 86) {
                if (ma >= aa[t] - fx - mnobia - 4000 && ma <= aa[t] - fx + anobia[t] + 4000) {
                    draw_sprite_region(grap[152][3], xx[0] / 100, xx[1] / 100, mirror);
                } else {
                    draw_sprite_region(grap[86][3], xx[0] / 100, xx[1] / 100, mirror);
                }
            }

            if (atype[t] == 200)
                draw_sprite_region(grap[0][3], xx[0] / 100, xx[1] / 100, mirror);

            mirror = 0;
        }
    }

    // ブロック描画
    for (t = 0; t < tmax; t++) {
        xx[0] = ta[t] - fx;
        xx[1] = tb[t] - fy;
        xx[2] = 32;
        xx[3] = xx[2];
        if (xx[0] + xx[2] * 100 >= -10 && xx[1] <= fxmax) {

            xx[9] = 0;
            if (stagecolor == 2) {
                xx[9] = 30;
            }
            if (stagecolor == 4) {
                xx[9] = 60;
            }
            if (stagecolor == 5) {
                xx[9] = 90;
            }

            if (ttype[t] < 100) {
                xx[6] = ttype[t] + xx[9];
                draw_sprite_region(grap[xx[6]][1], xx[0] / 100, xx[1] / 100, mirror);
            }

            if (txtype[t] != 10) {

                if (ttype[t] == 100 || ttype[t] == 101 || ttype[t] == 102 || ttype[t] == 103 || ttype[t] == 104 && txtype[t] == 1 || ttype[t] == 114 && txtype[t] == 1 || ttype[t] == 116) {
                    xx[6] = 2 + xx[9];
                    draw_sprite_region(grap[xx[6]][1], xx[0] / 100, xx[1] / 100, mirror);
                }

                if (ttype[t] == 112 || ttype[t] == 104 && txtype[t] == 0 || ttype[t] == 115 && txtype[t] == 1) {
                    xx[6] = 1 + xx[9];
                    draw_sprite_region(grap[xx[6]][1], xx[0] / 100, xx[1] / 100, mirror);
                }

                if (ttype[t] == 111 || ttype[t] == 113 || ttype[t] == 115 && txtype[t] == 0 || ttype[t] == 124) {
                    xx[6] = 3 + xx[9];
                    draw_sprite_region(grap[xx[6]][1], xx[0] / 100, xx[1] / 100, mirror);
                }
            }

            if (ttype[t] == 117 && txtype[t] == 1) {
                draw_sprite_region(grap[4][5], xx[0] / 100, xx[1] / 100, mirror);
            }

            if (ttype[t] == 117 && txtype[t] >= 3) {
                draw_sprite_region(grap[3][5], xx[0] / 100, xx[1] / 100, mirror);
            }

            if (ttype[t] == 115 && txtype[t] == 3) {
                xx[6] = 1 + xx[9];
                draw_sprite_region(grap[xx[6]][1], xx[0] / 100, xx[1] / 100, mirror);
            }
            // ジャンプ台
            if (ttype[t] == 120 && txtype[t] != 1) {
                draw_sprite_region(grap[16][1], xx[0] / 100 + 3, xx[1] / 100 + 2, mirror);
            }
            // ON-OFF
            if (ttype[t] == 130)
                draw_sprite_region(grap[10][5], xx[0] / 100, xx[1] / 100, mirror);
            if (ttype[t] == 131)
                draw_sprite_region(grap[11][5], xx[0] / 100, xx[1] / 100, mirror);

            if (ttype[t] == 140)
                draw_sprite_region(grap[12][5], xx[0] / 100, xx[1] / 100, mirror);
            if (ttype[t] == 141)
                draw_sprite_region(grap[13][5], xx[0] / 100, xx[1] / 100, mirror);
            if (ttype[t] == 142)
                draw_sprite_region(grap[14][5], xx[0] / 100, xx[1] / 100, mirror);

            if (ttype[t] == 300 || ttype[t] == 301)
                draw_sprite_region(grap[1][5], xx[0] / 100, xx[1] / 100, mirror);

            // Pスイッチ
            if (ttype[t] == 400) {
                draw_sprite_region(grap[2][5], xx[0] / 100, xx[1] / 100, mirror);
            }
            // コイン
            if (ttype[t] == 800) {
                draw_sprite_region(grap[0][2], xx[0] / 100 + 2, xx[1] / 100 + 1, mirror);
            }
        }
    }

    // 地面(壁)//土管も
    for (t = 0; t < smax; t++) {
        if (sa[t] - fx + sc[t] >= -10 && sa[t] - fx <= fxmax + 1100) {

            if (stype[t] == 0) {
                set_draw_color(40, 200, 40);
                draw_rectangle_filled((sa[t] - fx) / 100, (sb[t] - fy) / 100, sc[t] / 100, sd[t] / 100);
                draw_rectangle_outline((sa[t] - fx) / 100, (sb[t] - fy) / 100, sc[t] / 100, sd[t] / 100);
            }
            // 土管
            if (stype[t] == 1) {
                set_draw_color(0, 230, 0);
                draw_rectangle_filled((sa[t] - fx) / 100, (sb[t] - fy) / 100, sc[t] / 100, sd[t] / 100);
                set_draw_color(0, 0, 0);

                draw_rectangle_outline((sa[t] - fx) / 100, (sb[t] - fy) / 100, sc[t] / 100, sd[t] / 100);
            }
            // 土管(下)
            if (stype[t] == 2) {
                set_draw_color(0, 230, 0);
                draw_rectangle_filled((sa[t] - fx) / 100, (sb[t] - fy) / 100 + 1, sc[t] / 100, sd[t] / 100);
                set_draw_color(0, 0, 0);

                draw_line((sa[t] - fx) / 100, (sb[t] - fy) / 100, (sa[t] - fx) / 100, (sb[t] - fy) / 100 + sd[t] / 100);
                draw_line((sa[t] - fx) / 100 + sc[t] / 100, (sb[t] - fy) / 100, (sa[t] - fx) / 100 + sc[t] / 100, (sb[t] - fy) / 100 + sd[t] / 100);
            }
            // 土管(横)
            if (stype[t] == 5) {
                set_draw_color(0, 230, 0);
                draw_rectangle_filled((sa[t] - fx) / 100, (sb[t] - fy) / 100 + 1, sc[t] / 100, sd[t] / 100);
                set_draw_color(0, 0, 0);
                draw_line((sa[t] - fx) / 100, (sb[t] - fy) / 100, (sa[t] - fx) / 100 + sc[t] / 100, (sb[t] - fy) / 100);
                draw_line((sa[t] - fx) / 100, (sb[t] - fy) / 100 + sd[t] / 100, (sa[t] - fx) / 100 + sc[t] / 100, (sb[t] - fy) / 100 + sd[t] / 100);
            }
            // 落ちてくるブロック
            if (stype[t] == 51) {
                if (sxtype[t] == 0) {
                    for (t3 = 0; t3 <= sc[t] / 3000; t3++) {
                        draw_sprite_region(grap[1][1], (sa[t] - fx) / 100 + 29 * t3, (sb[t] - fy) / 100, mirror);
                    }
                }
                if (sxtype[t] == 1 || sxtype[t] == 2) {
                    for (t3 = 0; t3 <= sc[t] / 3000; t3++) {
                        draw_sprite_region(grap[31][1], (sa[t] - fx) / 100 + 29 * t3, (sb[t] - fy) / 100, mirror);
                    }
                }
                if (sxtype[t] == 3 || sxtype[t] == 4) {
                    for (t3 = 0; t3 <= sc[t] / 3000; t3++) {
                        for (t2 = 0; t2 <= sd[t] / 3000; t2++) {
                            draw_sprite_region(grap[65][1], (sa[t] - fx) / 100 + 29 * t3, (sb[t] - fy) / 100 + 29 * t2, mirror);
                        }
                    }
                }

                if (sxtype[t] == 10) {
                    for (t3 = 0; t3 <= sc[t] / 3000; t3++) {
                        draw_sprite_region(grap[65][1], (sa[t] - fx) / 100 + 29 * t3, (sb[t] - fy) / 100, mirror);
                    }
                }

            }

            // 落ちるやつ
            if (stype[t] == 52) {
                xx[29] = 0;
                if (stagecolor == 2) {
                    xx[29] = 30;
                }
                if (stagecolor == 4) {
                    xx[29] = 60;
                }
                if (stagecolor == 5) {
                    xx[29] = 90;
                }

                for (t3 = 0; t3 <= sc[t] / 3000; t3++) {
                    if (sxtype[t] == 0) {
                        draw_sprite_region(grap[5 + xx[29]][1], (sa[t] - fx) / 100 + 29 * t3, (sb[t] - fy) / 100, mirror);
                        if (stagecolor != 4) {
                            draw_sprite_region(grap[6 + xx[29]][1], (sa[t] - fx) / 100 + 29 * t3, (sb[t] - fy) / 100 + 29, mirror);
                        } else {
                            draw_sprite_region(grap[5 + xx[29]][1], (sa[t] - fx) / 100 + 29 * t3, (sb[t] - fy) / 100 + 29, mirror);
                        }
                    }
                    if (sxtype[t] == 1) {
                        for (t2 = 0; t2 <= sd[t] / 3000; t2++) {
                            draw_sprite_region(grap[1 + xx[29]][1], (sa[t] - fx) / 100 + 29 * t3, (sb[t] - fy) / 100 + 29 * t2, mirror);
                        }
                    }

                    if (sxtype[t] == 2) {
                        for (t2 = 0; t2 <= sd[t] / 3000; t2++) {
                            draw_sprite_region(grap[5 + xx[29]][1], (sa[t] - fx) / 100 + 29 * t3, (sb[t] - fy) / 100 + 29 * t2, mirror);
                        }
                    }
                }
            }
            // ステージトラップ
            if (trap == 1) {
                if (stype[t] >= 100 && stype[t] <= 299) {
                    if (stagecolor == 1 || stagecolor == 3 || stagecolor == 5)
                        set_draw_color(0, 0, 0);
                    if (stagecolor == 2 || stagecolor == 4)
                        set_draw_color(255, 255, 255);
                    draw_rectangle_outline((sa[t] - fx) / 100, (sb[t] - fy) / 100, sc[t] / 100, sd[t] / 100);
                }
            }
            // ゴール
            if (stype[t] == 300) {
                set_draw_color(255, 255, 255);

                draw_rectangle_filled((sa[t] - fx) / 100 + 10, (sb[t] - fy) / 100, 10, sd[t] / 100 - 8);
                set_draw_color(0, 0, 0);

                draw_rectangle_outline((sa[t] - fx) / 100 + 10, (sb[t] - fy) / 100, 10, sd[t] / 100 - 8);
                set_draw_color(250, 250, 0);
                draw_circle_filled((sa[t] - fx) / 100 + 15 - 1, (sb[t] - fy) / 100, 10);
                set_draw_color(0, 0, 0);

                draw_circle_outline((sa[t] - fx) / 100 + 15 - 1, (sb[t] - fy) / 100, 10);
            }
            // 中間
            if (stype[t] == 500) {
                draw_sprite_region(grap[20][4], (sa[t] - fx) / 100, (sb[t] - fy) / 100, mirror);
            }
        }
    }

    // 描画上書き(土管)
    for (t = 0; t < smax; t++) {
        if (sa[t] - fx + sc[t] >= -10 && sa[t] - fx <= fxmax + 1100) {

            // 入る土管(右)
            if (stype[t] == 40) {
                set_draw_color(0, 230, 0);
                draw_rectangle_filled((sa[t] - fx) / 100, (sb[t] - fy) / 100 + 1, sc[t] / 100, sd[t] / 100);
                set_draw_color(0, 0, 0);

                draw_rectangle_outline((sa[t] - fx) / 100, (sb[t] - fy) / 100 + 1, sc[t] / 100, sd[t] / 100);
            }
            // とぶ土管
            if (stype[t] == 50) {
                set_draw_color(0, 230, 0);
                draw_rectangle_filled((sa[t] - fx) / 100 + 5, (sb[t] - fy) / 100 + 30, 50, sd[t] / 100 - 30);
                set_draw_color(0, 0, 0);
                draw_line((sa[t] - fx) / 100 + 5, (sb[t] - fy) / 100 + 30, (sa[t] - fx) / 100 + 5, (sb[t] - fy) / 100 + sd[t] / 100);
                draw_line((sa[t] - fx) / 100 + 5 + 50, (sb[t] - fy) / 100 + 30, (sa[t] - fx) / 100 + 50 + 5, (sb[t] - fy) / 100 + sd[t] / 100);

                set_draw_color(0, 230, 0);
                draw_rectangle_filled((sa[t] - fx) / 100, (sb[t] - fy) / 100 + 1, 60, 30);
                set_draw_color(0, 0, 0);

                draw_rectangle_outline((sa[t] - fx) / 100, (sb[t] - fy) / 100 + 1, 60, 30);
            }
            // 地面(ブロック)
            if (stype[t] == 200) {
                for (t3 = 0; t3 <= sc[t] / 3000; t3++) {
                    for (t2 = 0; t2 <= sd[t] / 3000; t2++) {
                        draw_sprite_region(grap[65][1], (sa[t] - fx) / 100 + 29 * t3, (sb[t] - fy) / 100 + 29 * t2, mirror);
                    }
                }
            }
        }
    }

    // ファイアバー
    for (t = 0; t < amax; t++) {

        xx[0] = aa[t] - fx;
        xx[1] = ab[t] - fy;
        xx[14] = 12000;
        xx[16] = 0;
        if (atype[t] == 87 || atype[t] == 88) {
            if (xx[0] + xx[2] * 100 >= -10 - xx[14] && xx[1] <= fxmax + xx[14] && xx[1] + xx[3] * 100 >= -10 && xx[3] <= fymax) {

                for (tt = 0; tt <= axtype[t] % 100; tt++) {
                    xx[26] = 18;
                    xd[4] = tt * xx[26] * cos(atm[t] * FM_PI / 180 / 2);
                    xd[5] = tt * xx[26] * sin(atm[t] * FM_PI / 180 / 2);
                    xx[24] = (int)xd[4];
                    xx[25] = (int)xd[5];
                    set_draw_color(230, 120, 0);
                    xx[23] = 8;
                    if (atype[t] == 87) {
                        draw_circle_filled(xx[0] / 100 + xx[24], xx[1] / 100 + xx[25], xx[23]);
                        set_draw_color(0, 0, 0);
                        draw_circle_outline(xx[0] / 100 + xx[24], xx[1] / 100 + xx[25], xx[23]);
                    } else {
                        draw_circle_filled(xx[0] / 100 - xx[24], xx[1] / 100 + xx[25], xx[23]);
                        set_draw_color(0, 0, 0);
                        draw_circle_outline(xx[0] / 100 - xx[24], xx[1] / 100 + xx[25], xx[23]);
                    }
                }
            }
        }
    }

    // プレイヤーのメッセージ
    set_draw_color(0, 0, 0);

    if (mmsgtm >= 1) {
        mmsgtm--;
        xs[0] = "";

        if (mmsgtype == 1)
            xs[0] = "お、おいしい!!";
        if (mmsgtype == 2)
            xs[0] = "毒は無いが……";
        if (mmsgtype == 3)
            xs[0] = "刺さった!!";
        if (mmsgtype == 10)
            xs[0] = "食べるべきではなかった!!";
        if (mmsgtype == 11)
            xs[0] = "俺は燃える男だ!!";
        if (mmsgtype == 50)
            xs[0] = "体が……焼ける……";
        if (mmsgtype == 51)
            xs[0] = "たーまやー!!";
        if (mmsgtype == 52)
            xs[0] = "見事にオワタ";
        if (mmsgtype == 53)
            xs[0] = "足が、足がぁ!!";
        if (mmsgtype == 54)
            xs[0] = "流石は摂氏800度!!";
        if (mmsgtype == 55)
            xs[0] = "溶岩と合体したい……";

        set_draw_color(0, 0, 0);

        draw_text(xs[0], (ma + mnobia + 300) / 100 - 1, mb / 100 - 1);
        draw_text(xs[0], (ma + mnobia + 300) / 100 + 1, mb / 100 + 1);
        set_draw_color(255, 255, 255);

        draw_text(xs[0], (ma + mnobia + 300) / 100, mb / 100);

    }

    // 敵キャラのメッセージ
    set_draw_color(0, 0, 0);

    for (t = 0; t < amax; t++) {
        if (amsgtm[t] >= 1) {
            amsgtm[t]--;

            xs[0] = "";

            if (amsgtype[t] == 1001)
                xs[0] = "ヤッフー!!";
            if (amsgtype[t] == 1002)
                xs[0] = "え?俺勝っちゃったの?";
            if (amsgtype[t] == 1003)
                xs[0] = "貴様の死に場所はここだ!";
            if (amsgtype[t] == 1004)
                xs[0] = "二度と会う事もないだろう";
            if (amsgtype[t] == 1005)
                xs[0] = "俺、最強!!";
            if (amsgtype[t] == 1006)
                xs[0] = "一昨日来やがれ!!";
            if (amsgtype[t] == 1007)
                xs[0] = "漢に後退の二文字は無い!!";
            if (amsgtype[t] == 1008)
                xs[0] = "ハッハァ!!";

            if (amsgtype[t] == 1011)
                xs[0] = "ヤッフー!!";
            if (amsgtype[t] == 1012)
                xs[0] = "え?俺勝っちゃったの?";
            if (amsgtype[t] == 1013)
                xs[0] = "貴様の死に場所はここだ!";
            if (amsgtype[t] == 1014)
                xs[0] = "身の程知らずが……";
            if (amsgtype[t] == 1015)
                xs[0] = "油断が死を招く";
            if (amsgtype[t] == 1016)
                xs[0] = "おめでたい奴だ";
            if (amsgtype[t] == 1017)
                xs[0] = "屑が!!";
            if (amsgtype[t] == 1018)
                xs[0] = "無謀な……";

            if (amsgtype[t] == 1021)
                xs[0] = "ヤッフー!!";
            if (amsgtype[t] == 1022)
                xs[0] = "え?俺勝っちゃったの?";
            if (amsgtype[t] == 1023)
                xs[0] = "二度と会う事もないだろう";
            if (amsgtype[t] == 1024)
                xs[0] = "身の程知らずが……";
            if (amsgtype[t] == 1025)
                xs[0] = "僕は……負けない!!";
            if (amsgtype[t] == 1026)
                xs[0] = "貴様に見切れる筋は無い";
            if (amsgtype[t] == 1027)
                xs[0] =
                    "今死ね、すぐ死ね、骨まで砕けろ!!";
            if (amsgtype[t] == 1028)
                xs[0] = "任務完了!!";

            if (amsgtype[t] == 1031)
                xs[0] = "ヤッフー!!";
            if (amsgtype[t] == 1032)
                xs[0] = "え?俺勝っちゃったの?";
            if (amsgtype[t] == 1033)
                xs[0] = "貴様の死に場所はここだ!";
            if (amsgtype[t] == 1034)
                xs[0] = "身の程知らずが……";
            if (amsgtype[t] == 1035)
                xs[0] = "油断が死を招く";
            if (amsgtype[t] == 1036)
                xs[0] = "おめでたい奴だ";
            if (amsgtype[t] == 1037)
                xs[0] = "屑が!!";
            if (amsgtype[t] == 1038)
                xs[0] = "無謀な……";

            if (amsgtype[t] == 15)
                xs[0] = "鉄壁!!よって、無敵!!";
            if (amsgtype[t] == 16)
                xs[0] = "丸腰で勝てるとでも?";
            if (amsgtype[t] == 17)
                xs[0] = "パリイ!!";
            if (amsgtype[t] == 18)
                xs[0] = "自業自得だ";
            if (amsgtype[t] == 20)
                xs[0] = "Zzz";
            if (amsgtype[t] == 21)
                xs[0] = "ク、クマー";
            if (amsgtype[t] == 24)
                xs[0] = "?";
            if (amsgtype[t] == 25)
                xs[0] = "食べるべきではなかった!!";
            if (amsgtype[t] == 30)
                xs[0] = "うめぇ!!";
            if (amsgtype[t] == 31)
                xs[0] = "ブロックを侮ったな?";
            if (amsgtype[t] == 32)
                xs[0] = "シャキーン";

            if (amsgtype[t] == 50)
                xs[0] = "波動砲!!";
            if (amsgtype[t] == 85)
                xs[0] = "裏切られたとでも思ったか?";
            if (amsgtype[t] == 86)
                xs[0] = "ポールアターック!!";

            if (amsgtype[t] != 31) {
                xx[5] = (aa[t] + anobia[t] + 300 - fx) / 100;
                xx[6] = (ab[t] - fy) / 100;
            } else {
                xx[5] = (aa[t] + anobia[t] + 300 - fx) / 100;
                xx[6] = (ab[t] - fy - 800) / 100;
            }

            set_draw_color(255, 255, 255);

            draw_text(xs[0], xx[5], xx[6]);
        }
    }

    message_box_draw();
    pause_menu_draw();

    // メッセージ
    if (mainmsgtype >= 1) {
        if (mainmsgtype == 1) {
            draw_text("WELCOME TO OWATA ZONE", 126, 100);
        }
        if (mainmsgtype == 1) {
            for (t2 = 0; t2 <= 2; t2++)
                draw_text("1", 88 + t2 * 143, 210);
        }
    }
}


void stagep() {

    //1-レンガ,2-コイン,3-空,4-土台//5-6地面//7-隠し//

    //1-1
    if (sta == 1 && stb == 1 && stc == 0) {
        level_load(level_1_1_0);
    }

    //1-2(地上)
    if (sta == 1 && stb == 2 && stc == 0) {
        level_load(level_1_2_0);
    }

    //1-2-1(地下)
    if (sta == 1 && stb == 2 && stc == 1) {
        level_load(level_1_2_1);
    }

    //1-2(地上)
    if (sta == 1 && stb == 2 && stc == 2) {
        level_load(level_1_2_2);
    }

    //1-3(地上)
    if (sta == 1 && stb == 3 && stc == 6) {
	    stc = 0;
    }

    if (sta == 1 && stb == 3 && stc == 0) {
        level_load(level_1_3_0);
    }

    //1-3(地下)
    if (sta == 1 && stb == 3 && stc == 1) {
        level_load(level_1_3_1);
    }

    //1-3(空中)
    if (sta == 1 && stb == 3 && stc == 5) {
        level_load(level_1_3_5);
    }

    //1-4(地下)
    if (sta == 1 && stb == 4 && stc == 0) {
        level_load(level_1_4_0);
    }

    // 2-1
    if (sta == 2 && stb == 1 && stc == 0) {
        level_load(level_2_1_0);
    }

    //2-2(地上)
    if (sta == 2 && stb == 2 && stc == 0) {	
        level_load(level_2_2_0);
    }

    //2-2(地下)
    if (sta == 2 && stb == 2 && stc == 1) {
        level_load(level_2_2_1);
    }

    // 2-2 地上
    if (sta == 2 && stb == 2 && stc == 2) {	
        level_load(level_2_2_2);
    }

    // 2-3
    if (sta == 2 && stb == 3 && stc == 0) {	
        level_load(level_2_3_0);
    }

    // 2-4(1番)
    if (sta == 2 && stb == 4 && (stc == 0 || stc == 10 || stc == 12)) {	
        level_load(level_2_4_0);
    }

    // 2-4(2番)
    if (sta == 2 && stb == 4 && stc == 1) {	
        level_load(level_2_4_1);
    }

    // 2-4(3番)
    if (sta == 2 && stb == 4 && stc == 2) {	
        level_load(level_2_4_2);
    }

    // 3-1
    if (sta == 3 && stb == 1 && stc == 0) {	
        level_load(level_3_1_0);
    }
}

//ブロック出現
void tyobi(int x, int y, int type) {

    ta[tco] = x * 100;
    tb[tco] = y * 100;
    ttype[tco] = type;

    tco++;
    if (tco >= tmax)
	tco = 0;
}

//ブロック破壊
void brockbreak(int t) {
    play_sound_effect(oto[3]);
    eyobi(ta[t] + 1200, tb[t] + 1200, 300, -1000, 0, 160, 1000, 1000, 1, 120);
    eyobi(ta[t] + 1200, tb[t] + 1200, -300, -1000, 0, 160, 1000, 1000, 1, 120);
    eyobi(ta[t] + 1200, tb[t] + 1200, 240, -1400, 0, 160, 1000, 1000, 1, 120);
    eyobi(ta[t] + 1200, tb[t] + 1200, -240, -1400, 0, 160, 1000, 1000, 1, 120);
    
    ta[t] = -800000;
}

//グラ作成
void
eyobi(int xa, int xb, int xc, int xd, int xe, int xf, int xnobia, int xnobib, int xgtype, int xtm) {

    ea[eco] = xa;
    eb[eco] = xb;
    ec[eco] = xc;
    ed[eco] = xd;
    ee[eco] = xe;
    ef[eco] = xf;
    egtype[eco] = xgtype;
    etm[eco] = xtm;
    enobia[eco] = xnobia;
    enobib[eco] = xnobib;

    eco++;
    if (eco >= emax)
	eco = 0;

}

//敵キャラ、アイテム作成
void ayobi(int xa, int xb, int xc, int xd, int xnotm, int xtype, int xxtype) {
    int rz = 0;
    for (t1 = 0; t1 <= 1; t1++) {
        t1 = 2;
        if (aa[aco] >= -9000 && aa[aco] <= 30000)
            t1 = 0;
        
        rz++;

        if (rz <= amax) {
            t1 = 3;

            aa[aco] = xa;
            ab[aco] = xb;
            ac[aco] = xc;
            ad[aco] = xd;
            if (xxtype > 100)
                ac[aco] = xxtype;

            atype[aco] = xtype;
            if (xxtype >= 0 && xxtype <= 99100)
                axtype[aco] = xxtype;

            anotm[aco] = xnotm;
            if (aa[aco] - fx <= ma + mnobia / 2)
                amuki[aco] = 1;

            if (aa[aco] - fx > ma + mnobia / 2)
                amuki[aco] = 0;

            if (abrocktm[aco] >= 1)
                amuki[aco] = 1;

            if (abrocktm[aco] == 20)
                amuki[aco] = 0;

            anobia[aco] = anx[atype[aco]];
            anobib[aco] = any[atype[aco]];

            // 大砲音
            if (xtype == 7) {
                play_sound_effect(oto[10]);
            }

            // ファイア音
            if (xtype == 10) {
                play_sound_effect(oto[18]);
            }

            azimentype[aco] = 1;

            if (xtype == 87) {
                atm[aco] = rand(179) + (-90);
            }

            aco += 1;
            if (aco >= amax - 1) {
                aco = 0;
            }
        }
    }
}

void spawn_decoration(int type, int x, int y) {
    na[nco] = x * 100;
	nb[nco] = y * 100;
	ntype[nco] = type;

    nco = (nco + 1) % nmax;
}

void spawn_platform(int type, int subtype, int fallSpeed, int x, int y, int width) {
    sra[srco] = x * 100;
    srb[srco] = y * 100;
    src[srco] = width * 100;
    sre[srco] = fallSpeed;
    sracttype[srco] = subtype;
    srsp[srco] = type;

    srco = (srco + 1) % srmax;
}

void set_enemy_spawn(int type, int subtype, int x, int y) {
	ba[bco] = x * 100;
	bb[bco] = y * 100;
	btype[bco] = type;
	bxtype[bco] = subtype;

    bco = (bco + 1) % bmax;
}

void spawn_general_object(int type, int subtype, int x, int y, int width, int height) {
    stype[sco] = type;
    sxtype[sco] = subtype;
    sa[sco] = x * 100;
    sb[sco] = y * 100;
    sc[sco] = width * 100;
    sd[sco] = height * 100;

    sco = (sco + 1) % smax;
}

static void play_exit(void) {
    message_box_reset();
}

const GameState STATE_PLAY = {
    .enter = play_enter,
    .update = play_update,
    .draw = play_draw,
    .exit = play_exit,
};