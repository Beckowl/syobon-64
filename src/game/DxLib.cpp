#include <libdragon.h>

#include "DxLib.h"
#include "sa_graphics.h"
#include "sa_input.h"
#include "sa_audio.h"

bool sound = true;

//Strings

void DrawString(int a, int b, const char *x, Uint32 c)
{
    draw_text(x, a, b);
}

void DrawFormatString(int a, int b, Uint32 color, const char *str, ...)
{
    va_list args;
    char *newstr = new char[strlen(str) + 16];
    va_start(args, str);
    vsprintf(newstr, str, args);
    va_end(args);
    DrawString(a, b, newstr, color);
    delete[] newstr;
}

byte CheckHitKey(int key)
{
    return is_button_down((CONT_BUTTON)key);
}

byte WaitKey()
{
    while (true) {
        joypad_poll();

	    joypad_buttons_t pressed = joypad_get_buttons_pressed(gMainController);

        if (pressed.raw) {
            return true; // ??
        }
    }
}

void DrawGraphZ(int a, int b, SDL_Surface * mx)
{
    if(mx)
    {
        draw_sprite(mx, a, b, false);
    }
}

void DrawTurnGraphZ(int a, int b, SDL_Surface * mx)
{
    if(mx)
    {
        draw_sprite(mx, a, b, true);
    }
}

void DrawVertTurnGraph(int a, int b, SDL_Surface * mx)
{
    // TODO: flip sprite vertically
    draw_sprite(mx, a, b, false);
}

SDL_Surface *DerivationGraph(int srcx, int srcy, int width, int height,
			     sprite_t * src)
{
    SpriteInfo* sprite = make_sprite(src, srcx, srcy, width, height);
    return sprite;
}

sprite_t *LoadGraph(const char *filename)
{
    return sprite_load(filename);
}

void PlaySoundMem(Mix_Chunk* s, int l)
{
    if(sound) {
        play_sound(s);
    }
}

Mix_Chunk* LoadSoundMem(const char* f)
{
    if(!sound) return NULL;

    return load_sound(f);
}

Mix_Music* LoadMusicMem(const char* f)
{
    if(!sound) return NULL;

    return load_sound(f);
}

