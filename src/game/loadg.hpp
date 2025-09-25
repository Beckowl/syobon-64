#include "global.hpp"

int x1;

void loadg(void) {
    for (t = 0; t < 51; t++) {
        mgrap[t] = 0;
    }
    for (int i = 0; i < 161; i++) {
        for (int j = 0; j < 8; j++) {
            grap[i][j] = NULL;
        }
    }

    // 画像読み込み

    // プレイヤー
    mgrap[0] = sprite_load("rom:/res/player.sprite");
    // ブロック
    mgrap[1] = sprite_load("rom:/res/brock.sprite");
    // アイテム
    mgrap[2] = sprite_load("rom:/res/item.sprite");
    // 敵
    mgrap[3] = sprite_load("rom:/res/teki.sprite");
    // 背景
    mgrap[4] = sprite_load("rom:/res/haikei.sprite");
    // ブロック2
    mgrap[5] = sprite_load("rom:/res/brock2.sprite");
    // おまけ
    mgrap[6] = sprite_load("rom:/res/omake.sprite");
    // おまけ2
    mgrap[7] = sprite_load("rom:/res/omake2.sprite");
    // タイトル
    mgrap[30] = sprite_load("rom:/res/syobon3.sprite");

    // プレイヤー読み込み
    grap[40][0] = get_sprite_region(mgrap[0], 0, 0, 30, 36);
    grap[0][0] = get_sprite_region(mgrap[0], 31 * 4, 0, 30, 36);
    grap[1][0] = get_sprite_region(mgrap[0], 31 * 1, 0, 30, 36);
    grap[2][0] = get_sprite_region(mgrap[0], 31 * 2, 0, 30, 36);
    grap[3][0] = get_sprite_region(mgrap[0], 31 * 3, 0, 30, 36);
    grap[41][0] = get_sprite_region(mgrap[6], 50, 0, 51, 73);

    x1 = 1;
    // ブロック読み込み
    for (t = 0; t <= 6; t++) {
        grap[t][x1] = get_sprite_region(mgrap[x1], 33 * t, 0, 30, 30);
        grap[t + 30][x1] = get_sprite_region(mgrap[x1], 33 * t, 33, 30, 30);
        grap[t + 60][x1] = get_sprite_region(mgrap[x1], 33 * t, 66, 30, 30);
        grap[t + 90][x1] = get_sprite_region(mgrap[x1], 33 * t, 99, 30, 30);
    }

    grap[8][x1] = get_sprite_region(mgrap[x1], 33 * 7, 0, 30, 30);
    grap[16][x1] = get_sprite_region(mgrap[2], 33 * 6, 0, 24, 27);
    grap[10][x1] = get_sprite_region(mgrap[x1], 33 * 9, 0, 30, 30);
    grap[40][x1] = get_sprite_region(mgrap[x1], 33 * 9, 33, 30, 30);
    grap[70][x1] = get_sprite_region(mgrap[x1], 33 * 9, 66, 30, 30);
    grap[100][x1] = get_sprite_region(mgrap[x1], 33 * 9, 99, 30, 30);

    // ブロック読み込み2
    x1 = 5;
    for (t = 0; t <= 6; t++) {
        grap[t][x1] = get_sprite_region(mgrap[x1], 33 * t, 0, 30, 30);
    }
    grap[10][5] = get_sprite_region(mgrap[x1], 33 * 1, 33, 30, 30);
    grap[11][5] = get_sprite_region(mgrap[x1], 33 * 2, 33, 30, 30);
    grap[12][5] = get_sprite_region(mgrap[x1], 33 * 0, 66, 30, 30);
    grap[13][5] = get_sprite_region(mgrap[x1], 33 * 1, 66, 30, 30);
    grap[14][5] = get_sprite_region(mgrap[x1], 33 * 2, 66, 30, 30);

    // アイテム読み込み
    x1 = 2;
    for (t = 0; t <= 5; t++) {
        grap[t][x1] = get_sprite_region(mgrap[x1], 33 * t, 0, 30, 30);
    }

    // 敵キャラ読み込み
    x1 = 3;
    grap[0][x1] = get_sprite_region(mgrap[x1], 33 * 0, 0, 30, 30);
    grap[1][x1] = get_sprite_region(mgrap[x1], 33 * 1, 0, 30, 43);
    grap[2][x1] = get_sprite_region(mgrap[x1], 33 * 2, 0, 30, 30);
    grap[3][x1] = get_sprite_region(mgrap[x1], 33 * 3, 0, 30, 44);
    grap[4][x1] = get_sprite_region(mgrap[x1], 33 * 4, 0, 33, 35);
    grap[5][x1] = get_sprite_region(mgrap[7], 0, 0, 37, 55);
    grap[6][x1] = get_sprite_region(mgrap[7], 38 * 2, 0, 36, 50);
    grap[150][x1] = get_sprite_region(mgrap[7], 38 * 2 + 37 * 2, 0, 36, 50);
    grap[7][x1] = get_sprite_region(mgrap[x1], 33 * 6 + 1, 0, 32, 32);
    grap[8][x1] = get_sprite_region(mgrap[7], 38 * 2 + 37 * 3, 0, 37, 47);
    grap[151][x1] = get_sprite_region(mgrap[7], 38 * 3 + 37 * 3, 0, 37, 47);
    grap[9][x1] = get_sprite_region(mgrap[x1], 33 * 7 + 1, 0, 26, 30);
    grap[10][x1] = get_sprite_region(mgrap[6], 214, 0, 46, 16);

    // モララー
    grap[30][x1] = get_sprite_region(mgrap[7], 0, 56, 30, 36);
    grap[155][x1] = get_sprite_region(mgrap[7], 31 * 3, 56, 30, 36);
    grap[31][x1] = get_sprite_region(mgrap[6], 50, 74, 49, 79);

    grap[80][x1] = get_sprite_region(mgrap[4], 151, 31, 70, 40);
    grap[81][x1] = get_sprite_region(mgrap[4], 151, 72, 70, 40);
    grap[130][x1] = get_sprite_region(mgrap[4], 151 + 71, 72, 70, 40);
    grap[82][x1] = get_sprite_region(mgrap[5], 33 * 1, 0, 30, 30);
    grap[83][x1] = get_sprite_region(mgrap[6], 0, 0, 49, 48);
    grap[84][x1] = get_sprite_region(mgrap[x1], 33 * 5 + 1, 0, 30, 30);
    grap[86][x1] = get_sprite_region(mgrap[6], 102, 66, 49, 59);
    grap[152][x1] = get_sprite_region(mgrap[6], 152, 66, 49, 59);

    grap[90][x1] = get_sprite_region(mgrap[6], 102, 0, 64, 63);

    grap[100][x1] = get_sprite_region(mgrap[2], 33 * 1, 0, 30, 30);
    grap[101][x1] = get_sprite_region(mgrap[2], 33 * 7, 0, 30, 30);
    grap[102][x1] = get_sprite_region(mgrap[2], 33 * 3, 0, 30, 30);

    grap[105][x1] = get_sprite_region(mgrap[2], 33 * 5, 0, 30, 30);
    grap[110][x1] = get_sprite_region(mgrap[2], 33 * 4, 0, 30, 30);

    // 背景読み込み
    x1 = 4;
    grap[0][x1] = get_sprite_region(mgrap[x1], 0, 0, 150, 90);
    grap[1][x1] = get_sprite_region(mgrap[x1], 151, 0, 65, 29);
    grap[2][x1] = get_sprite_region(mgrap[x1], 151, 31, 70, 40);
    grap[3][x1] = get_sprite_region(mgrap[x1], 0, 91, 100, 90);
    grap[4][x1] = get_sprite_region(mgrap[x1], 151, 113, 51, 29);
    grap[5][x1] = get_sprite_region(mgrap[x1], 222, 0, 28, 60);
    grap[6][x1] = get_sprite_region(mgrap[x1], 151, 143, 90, 40);
    grap[30][x1] = get_sprite_region(mgrap[x1], 293, 0, 149, 90);
    grap[31][x1] = get_sprite_region(mgrap[x1], 293, 92, 64, 29);

    // 中間フラグ
    grap[20][x1] = get_sprite_region(mgrap[x1], 40, 182, 40, 60);

    // グラ
    x1 = 5;
    grap[0][x1] = get_sprite_region(mgrap[6], 167, 0, 45, 45);

    // 敵サイズ収得

    x1 = 3;
    for (t = 0; t <= 140; t++) {
        if (grap[t][x1]) {
            anx[t] = grap[t][x1]->width;
            any[t] = grap[t][x1]->height;

            anx[t] *= 100;
            any[t] *= 100;
        } else {
            anx[t] = 0;
            any[t] = 0;
        }
    }

    anx[79] = 120 * 100;
    any[79] = 15 * 100;
    anx[85] = 25 * 100;
    any[85] = 30 * 10 * 100;

    // 背景サイズ収得
    x1 = 4;
    for (t = 0; t < 40; t++) {
        if (grap[t][x1]) {
            ne[t] = grap[t][x1]->width;
            nf[t] = grap[t][x1]->height;
        } else {
            ne[t] = 0;
            nf[t] = 0;
        }
    }

    otom[1] = wav64_load("rom:/BGM/field.wav64", NULL);   // 50
    otom[2] = wav64_load("rom:/BGM/dungeon.wav64", NULL); // 40
    otom[3] = wav64_load("rom:/BGM/star4.wav64", NULL);   // 50
    otom[4] = wav64_load("rom:/BGM/castle.wav64", NULL);  // 50
    otom[5] = wav64_load("rom:/BGM/puyo.wav64", NULL);    // 50

    oto[1] = wav64_load("rom:/SE/jump.wav64", NULL);
    oto[3] = wav64_load("rom:/SE/brockbreak.wav64", NULL);
    oto[4] = wav64_load("rom:/SE/coin.wav64", NULL);
    oto[5] = wav64_load("rom:/SE/humi.wav64", NULL);
    oto[6] = wav64_load("rom:/SE/koura.wav64", NULL);
    oto[7] = wav64_load("rom:/SE/dokan.wav64", NULL);
    oto[8] = wav64_load("rom:/SE/brockkinoko.wav64", NULL);
    oto[9] = wav64_load("rom:/SE/powerup.wav64", NULL);
    oto[10] = wav64_load("rom:/SE/kirra.wav64", NULL);
    oto[11] = wav64_load("rom:/SE/goal.wav64", NULL);
    oto[12] = wav64_load("rom:/SE/death.wav64", NULL);
    oto[13] = wav64_load("rom:/SE/Pswitch.wav64", NULL);
    oto[14] = wav64_load("rom:/SE/jumpBlock.wav64", NULL);
    oto[15] = wav64_load("rom:/SE/hintBlock.wav64", NULL);
    oto[16] = wav64_load("rom:/SE/4-clear.wav64", NULL);
    oto[17] = wav64_load("rom:/SE/allclear.wav64", NULL);
    oto[18] = wav64_load("rom:/SE/tekifire.wav64", NULL);
}