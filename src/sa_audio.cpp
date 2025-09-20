#include <libdragon.h>
#include "sa_audio.h"

static wav64_t* sCurrBgMusic;

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

wav64_t* load_sound(const char* path) {
    return wav64_load(path, NULL);
}

void free_sound(wav64_t* sound) {
    if (sound != NULL) { 
        wav64_close(sound);
    }
}

void set_background_music(wav64_t* music) {
    if (sCurrBgMusic) {
        stop_background_music();
    }

    wav64_play(music, CH_BGM);
    sCurrBgMusic = music;
}

void stop_background_music(void) {
    mixer_ch_stop(CH_BGM);
    sCurrBgMusic = NULL;
}

void play_sound_effect(wav64_t* sound) {
    for (int ch = CH_SFX1; ch < CH_COUNT; ++ch) {
        if (!mixer_ch_playing(ch)) {
            wav64_play(sound, ch);

            return;
        }
    }
}

void stop_sound_effects(void) {
    for (int ch = CH_SFX1; ch < CH_COUNT; ++ch) {
        mixer_ch_stop(ch);
    }
}