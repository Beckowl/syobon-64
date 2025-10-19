#include <libdragon.h>
#include "sa_audio.hpp"

static wav64_t* sActiveSounds[CH_COUNT];

void sa_audio_init(void) {
    audio_init(AUDIO_FREQ, NUM_AUDIO_BUFFERS);
    mixer_init(CH_COUNT);
}

void process_audio(void) {
    if (audio_can_write()) {
        short *buf = audio_write_begin();
        mixer_poll(buf, audio_get_buffer_length());
        audio_write_end();
    }
}

void set_background_music(wav64_t* music) {
    mixer_ch_stop(CH_BGM);
    wav64_play(music, CH_BGM);

    sActiveSounds[CH_BGM] = music;
}

void stop_background_music(void) {
    mixer_ch_stop(CH_BGM);
    sActiveSounds[CH_BGM] = NULL;
}

void play_sound_effect(wav64_t* sound) {
    int freeCh = 0;

    for (int ch = CH_SFX1; ch < CH_COUNT; ++ch) {
        bool playing = mixer_ch_playing(ch);

        if (sActiveSounds[ch] == sound && playing) {
            // sound is already playing, restart playback
            mixer_ch_set_pos(ch, 0);
            return;
        }
        
        // remember the first free channel
        if (!freeCh && !playing) {
            freeCh = ch;
        }
    }

    if (freeCh) {
        wav64_play(sound, freeCh);
        sActiveSounds[freeCh] = sound;
    }
}

void stop_sound_effects(void) {
    for (int ch = CH_SFX1; ch < CH_COUNT; ++ch) {
        mixer_ch_stop(ch);
        sActiveSounds[ch] = NULL;
    }
}
