#ifndef AUDIO_H
#define AUDIO_H

#include <libdragon.h>

enum AudioChannel {
    CH_BGM = 0,
    CH_SFX = 1
};

wav64_t* load_sound(const char* path);

void set_background_music(wav64_t* music);
void stop_background_music(void);

void play_sound(wav64_t* sound);
void stop_sound(void);

#endif