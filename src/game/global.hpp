#ifndef GLOBAL_H
#define GLOBAL_H

#include <libdragon.h>

#include "sa_graphics.hpp"

//ステージ
inline int stagecolor = 1;
inline int sta = 1, stb = 4, stc = 0;

//クイック
inline int fast = 1;

//トラップ表示
inline int trap = 1;

//中間ゲート
inline int tyuukan = 0;

//ステージ読み込みループ(いじらない)
inline int stagepoint;
//オーバーフローさせる
inline int over = 0;

//ステージスイッチ
inline int stageonoff = 0;

inline SpriteRegion *grap[161][8];
inline sprite_t *mgrap[51];

inline int mirror;

inline wav64_t *otom[6];
inline wav64_t *oto[19];

//ループ
inline int t, tt, t1, t2, t3, t4;

//地面
#define smax 31
inline int sco;
inline int sa[smax], sb[smax], sc[smax], sd[smax], stype[smax], sxtype[smax], sr[smax];
inline int sgtype[smax];

//プレイヤー
inline int mainmsgtype;
inline int ma, mb, mnobia, mnobib, mhp;
inline int mc, md, mactp, mact;
inline int nokori = 3;

inline int mtype, mxtype, mtm, mzz;
inline int mzimen, mrzimen, mkasok, mmuki, mjumptm, mkeytm;
inline int mmutekitm, mmutekion; // invincibility timer / invincible, gonna keep them because they're useful
inline int actaon[7];
//メッセージ
inline int mmsgtm, mmsgtype;

inline int mascrollmax = RECENTER_X(210) * 100;

//ブロック
#define tmax 641
inline int tco;
inline int ta[tmax], tb[tmax], thp[tmax], ttype[tmax];
inline int titem[tmax], txtype[tmax];

//効果を持たないグラ
#define emax 201
inline int eco;
inline int ea[emax], eb[emax], enobia[emax], enobib[emax], ec[emax], ed[emax];
inline int ee[emax], ef[emax], etm[emax];
inline int egtype[emax];

//敵キャラ
#define amax 24
inline int aco;
inline int aa[amax], ab[amax], anobia[amax], anobib[amax], ac[amax], ad[amax];
inline int ae[amax], af[amax], abrocktm[amax];
inline int aacta[amax], aactb[amax], azimentype[amax], axzimen[amax];
inline int atype[amax], axtype[amax], amuki[amax], ahp[amax];
inline int anotm[amax], anx[160], any[160];
inline int atm[amax];
inline int amsgtm[amax], amsgtype[amax];

//敵出現
#define bmax 81
inline int bco;
inline int ba[bmax], bb[bmax], btm[bmax];
inline int btype[bmax], bxtype[bmax], bz[bmax];

//背景
#define nmax 41
inline int nco;
inline int na[nmax], nb[nmax], ntype[nmax];
inline int ne[nmax], nf[nmax];

//リフト
#define srmax 21
inline int srco;
inline int sra[srmax], srb[srmax], src[srmax], srd[srmax], sre[srmax], srf[srmax];
inline int srtype[srmax], srgtype[srmax], sracttype[srmax], srsp[srmax];
inline int srmuki[srmax], sron[srmax];
inline int srsok[srmax], srmovep[srmax], srmove[srmax];

//スクロール範囲
inline int fx = 0, fy = 0, scrollx, scrolly;

//画面サイズ(ファミコンサイズ×2)(256-224)
inline int fxmax = SCREEN_WIDTH * 100, fymax = SCREEN_HEIGHT * 100;

//ステージ
inline unsigned char stagedate[17][2001];

//自由な値
inline int xx[91];
inline double xd[11];
inline const char* xs[31];

#endif