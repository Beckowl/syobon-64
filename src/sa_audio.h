#ifndef SA_AUDIO_H
#define SA_AUDIO_H

#define AUDIO_FREQ 16000
#define NUM_AUDIO_BUFFERS 2

#include <libdragon.h>

enum AudioChannel {
    CH_BGM = 0,
    CH_SFX1,
    CH_SFX2,
    CH_SFX3,
    CH_SFX4,
    CH_SFX5,
    CH_SFX6,
    CH_SFX7,
    CH_SFX8,
    CH_SFX9,
    CH_SFX10,
    CH_SFX11,
    CH_SFX12,
    CH_SFX13,
    CH_SFX14,
    CH_SFX15,
    CH_COUNT
};

void sa_audio_init(void);
void process_audio(void);

wav64_t* load_sound(const char* path);
void free_sound(wav64_t* sound);

void set_background_music(wav64_t* music);
void stop_background_music(void);
void play_sound_effect(wav64_t* sound);
void stop_sound_effects(void);

#endif