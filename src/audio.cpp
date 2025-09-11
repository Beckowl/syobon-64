#include <libdragon.h>
#include "audio.hpp"

#define AUDIO_FREQ 16000
#define NUM_BUFFERS 2

static wav64_t* sCurrBgMusic;

void initialize_audio(void) {
    audio_init(AUDIO_FREQ, NUM_BUFFERS);
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

void play_sound(wav64_t* sound) {
    for (int ch = CH_SFX1; ch < CH_COUNT; ++ch) {
        if (!mixer_ch_playing(ch)) {
            wav64_play(sound, ch);

            return;
        }
    }
}