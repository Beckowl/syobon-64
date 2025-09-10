#include <libdragon.h>

#define TRUE 1
#define FALSE 0
#define byte unsigned char

#define GetNowCount() (unsigned int)get_ticks_us()
#define GetColor(r, g, b) RGBA32(r, g, b, 0xFF)

//UNIMPLEMENTED - macro substitution
#define SetFontThickness(f);
#define StopSoundMem(s);
#define ChangeVolumeSoundMem(s, v);

// todo
#define DrawGraph(a, b, mx, z)
#define DrawTurnGraph(a, b, mx, z)
#define DerivationGraph(a, b, mx, z)