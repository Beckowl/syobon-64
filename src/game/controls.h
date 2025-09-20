#ifndef CONTROLS_H
#define CONTROLS_H

#include "sa_input.h"

#define BUTTON_NONE 		0							// placeholder button
#define BUTTON_JUMP 		(BUTTON_A | BUTTON_D_UP)
#define BUTTON_LEFT 		BUTTON_D_LEFT
#define BUTTON_RIGHT 		BUTTON_D_RIGHT
#define BUTTON_DOWN 		BUTTON_D_DOWN
#define BUTTON_SUICIDE		(BUTTON_L | BUTTON_R)		// press L+R to suicide
#define BUTTON_START_PAUSE 	BUTTON_START
#define BUTTON_PAGE_UP 		BUTTON_R					// title screen level select
#define BUTTON_PAGE_DOWN 	BUTTON_L					// title screen level select

#endif