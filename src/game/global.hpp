#ifndef GLOBAL_H
#define GLOBAL_H

#include <libdragon.h>
#include <string>

#include "sa_graphics.hpp"


using namespace std;

#define SHORT

#define INLINE inline

void game_init();
void game_update();
void game_draw();
void game_deinit();

void loadg();

//String 使用

//プログラム中
//main-10
//タイトル-100

//: This is unexcusable. How could someone in their right mind define
//: a variable called 'main'!?
//: The new define is after the main method
INLINE int mainZ = 100, maintm = 0;

//ステージ
INLINE int stagecolor = 1;
INLINE int sta = 1, stb = 4, stc = 0;

//クイック
INLINE int fast = 1;

//トラップ表示
INLINE int trap = 1;

//中間ゲート
INLINE int tyuukan = 0;


//スタッフロール
INLINE int ending = 0;


//ステージ読み込みループ(いじらない)
INLINE int stagerr, stagepoint;
//オーバーフローさせる
INLINE int over = 0;

//ステージスイッチ
INLINE int stageonoff = 0;


//メインプログラム
void game_update();
void game_draw();
INLINE int maint;


//サブクラス
//(ウエイト系
#define wait(i) { } // TODO: implement this
void wait2(long stime, long etime, int FLAME_TIME);
INLINE int rand(int Rand);
#define end() exit(0)

//描画
INLINE color_t color;
INLINE color_t gfxcolor;
void setfont(int a);
void setcolor(int red, int green, int blue);
void setc0();
void setc1();
void drawpixel(int a, int b);
void drawline(int a, int b, int c, int d);
void drawrect(int a, int b, int c, int d);
void fillrect(int a, int b, int c, int d);
void drawarc(int a, int b, int c, int d);
void fillarc(int a, int b, int c, int d);
void FillScreen();
INLINE SpriteRegion *grap[161][8];
INLINE sprite_t *mgrap[51];
sprite_t *loadimage(string b);
SpriteRegion *loadimage(int a, int x, int y, int r, int z);
INLINE int mirror;
void drawimage(SpriteRegion * mx, int a, int b);
void drawimage(SpriteRegion * mx, int a, int b, int c, int d, int e, int f);
void setre();
void setre2();
void setno();
INLINE wav64_t *otom[6];
INLINE wav64_t *oto[19];
void ot(wav64_t * x);
void bgmchange(wav64_t * x);

//文字
void str(string c, int a, int b);


//)

void stagecls();
void stage();
void stagep();





//1-ステージ
//10-ステージ前
//



//ループ
INLINE int t, tt, t1, t2, t3, t4;


//初期化
INLINE int zxon, zzxon;

//キーコンフィグ
INLINE int key, keytm;

//三角関数
INLINE double pai = 3.1415926535;


//地面
#define smax 31
INLINE int sx, sco;
INLINE int sa[smax], sb[smax], sc[smax], sd[smax], stype[smax], sxtype[smax],
    sr[smax];
INLINE int sgtype[smax];



//プレイヤー
INLINE int mainmsgtype;
INLINE int ma, mb, mnobia, mnobib, mhp;
INLINE int mc, md, macttype, atkon, atktm, mactsok, msstar, mactp, mact;
INLINE int nokori = 3;

INLINE int mtype, mxtype, mtm, mzz;
INLINE int mzimen, mrzimen, mkasok, mmuki, mmukitm, mjumptm, mkeytm, mcleartm;
INLINE int mmutekitm, mmutekion;
INLINE int mztm, mztype;
INLINE int actaon[7];
//メッセージ
INLINE int mmsgtm, mmsgtype;

INLINE int mascrollmax = RECENTER_X(210) * 100;




//ブロック
void tyobi(int x, int y, int type);
void brockbreak(int t);
#define tmax 641
INLINE int tco;
INLINE int ta[tmax], tb[tmax], tc[tmax], td[tmax], thp[tmax], ttype[tmax];
INLINE int titem[tmax], txtype[tmax];

//メッセージブロック
INLINE int tmsgtm, tmsgtype, tmsgx, tmsgy, tmsgnobix, tmsgnobiy, tmsg;
void ttmsg();
void txmsg(string x, int a);
void setfont(int x, int y);

//効果を持たないグラ
void eyobi(int xa, int xb, int xc, int xd, int xe, int xf, int xnobia, int xnobib, int xgtype, int xtm);
#define emax 201
INLINE int eco;
INLINE int ea[emax], eb[emax], enobia[emax], enobib[emax], ec[emax], ed[emax];
INLINE int ee[emax], ef[emax], etm[emax];
INLINE int egtype[emax];



//敵キャラ
void ayobi(int xa, int xb, int xc, int xd, int xnotm, int xtype, int xxtype);
void tekizimen();
#define amax 24
INLINE int aco;
INLINE int aa[amax], ab[amax], anobia[amax], anobib[amax], ac[amax], ad[amax];
INLINE int ae[amax], af[amax], abrocktm[amax];
INLINE int aacta[amax], aactb[amax], azimentype[amax], axzimen[amax];
INLINE int atype[amax], axtype[amax], amuki[amax], ahp[amax];
INLINE int anotm[amax], anx[160], any[160];
INLINE int atm[amax], a2tm[amax];
INLINE int amsgtm[amax], amsgtype[amax];

//敵出現
#define bmax 81
INLINE int bco;
INLINE int ba[bmax], bb[bmax], btm[bmax];
INLINE int btype[bmax], bxtype[bmax], bz[bmax];


//背景
#define nmax 41
INLINE int nxxmax, nco;
INLINE int na[nmax], nb[nmax], nc[nmax], nd[nmax], ntype[nmax];
INLINE int ne[nmax], nf[nmax], ng[nmax], nx[nmax];


//リフト
#define srmax 21
INLINE int srco;
INLINE int sra[srmax], srb[srmax], src[srmax], srd[srmax], sre[srmax], srf[srmax];
INLINE int srtype[srmax], srgtype[srmax], sracttype[srmax], srsp[srmax];
INLINE int srmuki[srmax], sron[srmax], sree[srmax];
INLINE int srsok[srmax], srmovep[srmax], srmove[srmax];





//スクロール範囲
INLINE int fx = 0, fy = 0, fzx, fzy, scrollx, scrolly;
//全体のポイント

//: "fma" already exists, so call it something else and add a define
INLINE int fmaZ = 0, fmb = 0;
#define fma fmaZ

//強制スクロール
INLINE int kscroll = 0;
//画面サイズ(ファミコンサイズ×2)(256-224)
INLINE int fxmax = SCREEN_WIDTH * 100, fymax = SCREEN_HEIGHT * 100;



//ステージ
INLINE unsigned char stagedate[17][2001];

//画面黒
INLINE int blacktm = 1, blackx = 0;



//自由な値
INLINE int xx[91];
INLINE double xd[11];
INLINE string xs[31];


//タイマー測定
//: Do with this what we did with fma
INLINE long stimeZ;
#define stime stimeZ

#endif