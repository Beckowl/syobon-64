#include <libdragon.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <string>

#include "sa_graphics.hpp"

#define TRUE 1
#define FALSE 0
#define byte unsigned char

#define ScreenFlip() { }	// buffer swapping will be handled by src/main.cpp
#define GetNowCount() get_ticks_us()

//UNIMPLEMENTED - macro substitution
#define SetFontThickness(f);
#define StopSoundMem(s);
#define ChangeVolumeSoundMem(s, v);

//Sound
#define DX_PLAYTYPE_LOOP -1
#define DX_PLAYTYPE_BACK 0

// this is temporary
typedef wav64_t Mix_Chunk;
typedef wav64_t Mix_Music;
typedef SpriteInfo SDL_Surface;
typedef unsigned int Uint32; // is it really undefined?? is vscode trippin?

void PlaySoundMem(Mix_Chunk* s, int l);
Mix_Chunk* LoadSoundMem(const char* f);
Mix_Music* LoadMusicMem(const char* f);
#define CheckSoundMem(s) !s

//Main screen
extern SDL_Surface *screen;

//Strings & fonts
#define SetFontSize(size) { }
#define ChangeFontType(type) { }

void DrawString(int a, int b, const char *x, color_t c);
void DrawFormatString(int a, int b, color_t color, const char *str, ...);

#define UpdateKeys() { }
#define ProcessMessage() { }
byte CheckHitKey(int key);
byte WaitKey();

#define GetColor(r, g, b) RGBA32(r, g, b, 0xFF)

//Uint32 GetColor(byte r, byte g, byte b);

#define DrawGraph(a, b, mx, z) DrawGraphZ(a, b, mx)
void DrawGraphZ(int a, int b, SDL_Surface * mx);

#define DrawTurnGraph(a, b, mx, z) DrawTurnGraphZ(a, b, mx)
void DrawTurnGraphZ(int a, int b, SDL_Surface * mx);

//#define DrawVertTurnGraph(x, y, e, a, mx, z) DrawRotaGraphZ(x, y, a, mx)
void DrawVertTurnGraph(int a, int b, SDL_Surface * mx);

SDL_Surface *DerivationGraph(int srcx, int srcy, int width, int height,
			     sprite_t * src);

//Noticably different than the original
sprite_t *LoadGraph(const char *filename);
