#ifndef CONTROLS_H
#define CONTROLS_H

#include "sa_input.h"

#define CONTROL_NONE 		0							// placeholder button
#define CONTROL_JUMP 		(BUTTON_A | BUTTON_D_UP)
#define CONTROL_LEFT 		BUTTON_D_LEFT
#define CONTROL_RIGHT 		BUTTON_D_RIGHT
#define CONTROL_DOWN 		BUTTON_D_DOWN
#define CONTROL_SUICIDE		(BUTTON_L | BUTTON_R)		// press L+R to suicide
#define CONTROL_START_PAUSE BUTTON_START
#define CONTROL_PAGE_UP 	BUTTON_R					// title screen level select
#define CONTROL_PAGE_DOWN 	BUTTON_L					// title screen level select

#endif