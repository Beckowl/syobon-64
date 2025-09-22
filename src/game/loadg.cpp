#include "DxLib.hpp"
#include "global.hpp"

int x1;

void loadg(void)
{

    for (t = 0; t < 51; t++) {
	mgrap[t] = 0;
    }
    for (int i = 0; i < 161; i++)
	for (int j = 0; j < 8; j++)
	    grap[i][j] = NULL;

/*
for (t=0;t<161;t++){
for (tt=0;tt<8;tt++){
grap[t][tt]=0;
}}
*/

//ma-=100;//mb==5000;
//end();


//画像読み込み

// 透過色を変更
//SetTransColor( 9*16+9 , 255 , 255 ) ;

//プレイヤー
    mgrap[0] = LoadGraph("rom:/res/player.sprite");
//ブロック
    mgrap[1] = LoadGraph("rom:/res/brock.sprite");
//アイテム
    mgrap[2] = LoadGraph("rom:/res/item.sprite");
//敵
    mgrap[3] = LoadGraph("rom:/res/teki.sprite");
//背景
    mgrap[4] = LoadGraph("rom:/res/haikei.sprite");
//ブロック2
    mgrap[5] = LoadGraph("rom:/res/brock2.sprite");
//おまけ
    mgrap[6] = LoadGraph("rom:/res/omake.sprite");
//おまけ2
    mgrap[7] = LoadGraph("rom:/res/omake2.sprite");
//タイトル
    mgrap[30] = LoadGraph("rom:/res/syobon3.sprite");


//プレイヤー読み込み
    grap[40][0] = DerivationGraph(0, 0, 30, 36, mgrap[0]);
    grap[0][0] = DerivationGraph(31 * 4, 0, 30, 36, mgrap[0]);
    grap[1][0] = DerivationGraph(31 * 1, 0, 30, 36, mgrap[0]);
    grap[2][0] = DerivationGraph(31 * 2, 0, 30, 36, mgrap[0]);
    grap[3][0] = DerivationGraph(31 * 3, 0, 30, 36, mgrap[0]);
    grap[41][0] = DerivationGraph(50, 0, 51, 73, mgrap[6]);

    x1 = 1;
//ブロック読み込み
    for (t = 0; t <= 6; t++) {
	grap[t][x1] = DerivationGraph(33 * t, 0, 30, 30, mgrap[x1]);
	grap[t + 30][x1] = DerivationGraph(33 * t, 33, 30, 30, mgrap[x1]);
	grap[t + 60][x1] = DerivationGraph(33 * t, 66, 30, 30, mgrap[x1]);
	grap[t + 90][x1] = DerivationGraph(33 * t, 99, 30, 30, mgrap[x1]);
    }
    grap[8][x1] = DerivationGraph(33 * 7, 0, 30, 30, mgrap[x1]);
    grap[16][x1] = DerivationGraph(33 * 6, 0, 24, 27, mgrap[2]);
    grap[10][x1] = DerivationGraph(33 * 9, 0, 30, 30, mgrap[x1]);
    grap[40][x1] = DerivationGraph(33 * 9, 33, 30, 30, mgrap[x1]);
    grap[70][x1] = DerivationGraph(33 * 9, 66, 30, 30, mgrap[x1]);
    grap[100][x1] = DerivationGraph(33 * 9, 99, 30, 30, mgrap[x1]);
//ブロック読み込み2
    x1 = 5;
    for (t = 0; t <= 6; t++) {
	grap[t][x1] = DerivationGraph(33 * t, 0, 30, 30, mgrap[x1]);
    }
    grap[10][5] = DerivationGraph(33 * 1, 33, 30, 30, mgrap[x1]);
    grap[11][5] = DerivationGraph(33 * 2, 33, 30, 30, mgrap[x1]);
    grap[12][5] = DerivationGraph(33 * 0, 66, 30, 30, mgrap[x1]);
    grap[13][5] = DerivationGraph(33 * 1, 66, 30, 30, mgrap[x1]);
    grap[14][5] = DerivationGraph(33 * 2, 66, 30, 30, mgrap[x1]);

//アイテム読み込み
    x1 = 2;
    for (t = 0; t <= 5; t++) {
	grap[t][x1] = DerivationGraph(33 * t, 0, 30, 30, mgrap[x1]);
    }

//敵キャラ読み込み
    x1 = 3;
    grap[0][x1] = DerivationGraph(33 * 0, 0, 30, 30, mgrap[x1]);
    grap[1][x1] = DerivationGraph(33 * 1, 0, 30, 43, mgrap[x1]);
    grap[2][x1] = DerivationGraph(33 * 2, 0, 30, 30, mgrap[x1]);
    grap[3][x1] = DerivationGraph(33 * 3, 0, 30, 44, mgrap[x1]);
    grap[4][x1] = DerivationGraph(33 * 4, 0, 33, 35, mgrap[x1]);
    grap[5][x1] = DerivationGraph(0, 0, 37, 55, mgrap[7]);
    grap[6][x1] = DerivationGraph(38 * 2, 0, 36, 50, mgrap[7]);
    grap[150][x1] = DerivationGraph(38 * 2 + 37 * 2, 0, 36, 50, mgrap[7]);
    grap[7][x1] = DerivationGraph(33 * 6 + 1, 0, 32, 32, mgrap[x1]);
    grap[8][x1] = DerivationGraph(38 * 2 + 37 * 3, 0, 37, 47, mgrap[7]);
    grap[151][x1] = DerivationGraph(38 * 3 + 37 * 3, 0, 37, 47, mgrap[7]);
    grap[9][x1] = DerivationGraph(33 * 7 + 1, 0, 26, 30, mgrap[x1]);
    grap[10][x1] = DerivationGraph(214, 0, 46, 16, mgrap[6]);

//モララー
    grap[30][x1] = DerivationGraph(0, 56, 30, 36, mgrap[7]);
    grap[155][x1] = DerivationGraph(31 * 3, 56, 30, 36, mgrap[7]);
    grap[31][x1] = DerivationGraph(50, 74, 49, 79, mgrap[6]);


    grap[80][x1] = DerivationGraph(151, 31, 70, 40, mgrap[4]);
    grap[81][x1] = DerivationGraph(151, 72, 70, 40, mgrap[4]);
    grap[130][x1] = DerivationGraph(151 + 71, 72, 70, 40, mgrap[4]);
    grap[82][x1] = DerivationGraph(33 * 1, 0, 30, 30, mgrap[5]);
    grap[83][x1] = DerivationGraph(0, 0, 49, 48, mgrap[6]);
    grap[84][x1] = DerivationGraph(33 * 5 + 1, 0, 30, 30, mgrap[x1]);
    grap[86][x1] = DerivationGraph(102, 66, 49, 59, mgrap[6]);
    grap[152][x1] = DerivationGraph(152, 66, 49, 59, mgrap[6]);

    grap[90][x1] = DerivationGraph(102, 0, 64, 63, mgrap[6]);

    grap[100][x1] = DerivationGraph(33 * 1, 0, 30, 30, mgrap[2]);
    grap[101][x1] = DerivationGraph(33 * 7, 0, 30, 30, mgrap[2]);
    grap[102][x1] = DerivationGraph(33 * 3, 0, 30, 30, mgrap[2]);

//grap[104][x1] = DerivationGraph( 33*2, 0, 30, 30, mgrap[5]) ;
    grap[105][x1] = DerivationGraph(33 * 5, 0, 30, 30, mgrap[2]);
    grap[110][x1] = DerivationGraph(33 * 4, 0, 30, 30, mgrap[2]);


//背景読み込み
    x1 = 4;
    grap[0][x1] = DerivationGraph(0, 0, 150, 90, mgrap[x1]);
    grap[1][x1] = DerivationGraph(151, 0, 65, 29, mgrap[x1]);
    grap[2][x1] = DerivationGraph(151, 31, 70, 40, mgrap[x1]);
    grap[3][x1] = DerivationGraph(0, 91, 100, 90, mgrap[x1]);
    grap[4][x1] = DerivationGraph(151, 113, 51, 29, mgrap[x1]);
    grap[5][x1] = DerivationGraph(222, 0, 28, 60, mgrap[x1]);
    grap[6][x1] = DerivationGraph(151, 143, 90, 40, mgrap[x1]);
    grap[30][x1] = DerivationGraph(293, 0, 149, 90, mgrap[x1]);
    grap[31][x1] = DerivationGraph(293, 92, 64, 29, mgrap[x1]);

//中間フラグ
    grap[20][x1] = DerivationGraph(40, 182, 40, 60, mgrap[x1]);


//グラ
    x1 = 5;
    grap[0][x1] = DerivationGraph(167, 0, 45, 45, mgrap[6]);









//敵サイズ収得
//int GrHandle=0;
    x1 = 3;
    for (t = 0; t <= 140; t++) {
	if (grap[t][x1]) {
	    anx[t] = grap[t][x1]->width;
	    any[t] = grap[t][x1]->height;
//GetGraphSize(grap[t][x1] ,&anx[t] ,&any[t]);
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

//背景サイズ収得
    x1 = 4;
    for (t = 0; t < 40; t++) {
	if (grap[t][x1]) {
	    ne[t] = grap[t][x1]->width;
	    nf[t] = grap[t][x1]->height;
//GetGraphSize(grap[t][x1] ,&ne[t] ,&nf[t]);
//ne[t]*=100;nf[t]*=100;
	} else {
	    ne[t] = 0;
	    nf[t] = 0;
	}
    }

/*
anx[0]=30;any[0]=30;
anx[1]=30;any[1]=43;
anx[2]=30;any[2]=30;
anx[3]=30;any[3]=44;
*/









//ogg読み込み
//try{
//oto[2] = LoadSoundMem( "SE/1.mp3" ) ;
    otom[1] = LoadMusicMem("rom:/BGM/field.wav64"); //50
    otom[2] = LoadMusicMem("rom:/BGM/dungeon.wav64"); //40
    otom[3] = LoadMusicMem("rom:/BGM/star4.wav64"); //50
    otom[4] = LoadMusicMem("rom:/BGM/castle.wav64"); //50
    otom[5] = LoadMusicMem("rom:/BGM/puyo.wav64"); //50
//otom[6]=LoadMusicMem( "BGM/last.wav64");
//ChangeVolumeSoundMem(50, otom[6]);

    oto[1] = LoadSoundMem("rom:/SE/jump.wav64");
//oto[2] = LoadSoundMem("rom:/SE/brockcoin.wav64");
    oto[3] = LoadSoundMem("rom:/SE/brockbreak.wav64");
    oto[4] = LoadSoundMem("rom:/SE/coin.wav64");
    oto[5] = LoadSoundMem("rom:/SE/humi.wav64");
    oto[6] = LoadSoundMem("rom:/SE/koura.wav64");
    oto[7] = LoadSoundMem("rom:/SE/dokan.wav64");
    oto[8] = LoadSoundMem("rom:/SE/brockkinoko.wav64");
    oto[9] = LoadSoundMem("rom:/SE/powerup.wav64");
    oto[10] = LoadSoundMem("rom:/SE/kirra.wav64");
    oto[11] = LoadSoundMem("rom:/SE/goal.wav64");
    oto[12] = LoadSoundMem("rom:/SE/death.wav64");
    oto[13] = LoadSoundMem("rom:/SE/Pswitch.wav64");
    oto[14] = LoadSoundMem("rom:/SE/jumpBlock.wav64");
    oto[15] = LoadSoundMem("rom:/SE/hintBlock.wav64");
    oto[16] = LoadSoundMem("rom:/SE/4-clear.wav64");
    oto[17] = LoadSoundMem("rom:/SE/allclear.wav64");
    oto[18] = LoadSoundMem("rom:/SE/tekifire.wav64");

//}catch( int num){end();}


//ループ設定-20000-20秒
//SetLoopPosSoundMem( 1,oto[104]) ;
//SetLoopSamplePosSoundMem(44100,oto[104]);
//SetLoopSamplePosSoundMem(22050,oto[104]);

}

inline bool sound;