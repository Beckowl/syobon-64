#include <libdragon.h>

#include "game.hpp"
#include "death_screen.hpp"

#include "sa_graphics.hpp"

#define DEATH_SCREEN_DURATION 30
static int sDeathScreenTimer = 0;

void death_screen_enter(void) {
    sDeathScreenTimer = 0;
    zxon = 0;
	mainZ = 10;
}

void death_screen_exit(void) {
    maintm = 0;
	mainZ = 1;
	zxon = 0;
}

void death_screen_update(void) {
    sDeathScreenTimer++;
    
    // it seems fast will always be 0 during gameplay?? not sure though
	if (fast == 1) {
	    sDeathScreenTimer += 2;
    }

	if (sDeathScreenTimer >= DEATH_SCREEN_DURATION) {
	   death_screen_exit();
	}
}

void death_screen_draw(void) {
    rdpq_clear(RGBA32(0, 0, 0, 0));

	draw_sprite(grap[0][0], RECENTER_X(190), 190);

    char buf[16];
    snprintf(buf, sizeof(buf), " × %d", nokori);

	draw_text(buf, RECENTER_X(230), 218);
}
