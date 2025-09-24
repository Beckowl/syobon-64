#ifndef CONTROLS_H
#define CONTROLS_H

#include "sa_input.hpp"

#define CONTROL_NONE 		(CONT_BUTTON)0							// placeholder button
#define CONTROL_JUMP 		(CONT_BUTTON)(BUTTON_A | BUTTON_D_UP)
#define CONTROL_LEFT 		BUTTON_D_LEFT
#define CONTROL_RIGHT 		BUTTON_D_RIGHT
#define CONTROL_DOWN 		BUTTON_D_DOWN
#define CONTROL_SUICIDE		(CONT_BUTTON)(BUTTON_L | BUTTON_R)		// press L+R to suicide
#define CONTROL_START_PAUSE BUTTON_START
#define CONTROL_PAGE_UP 	BUTTON_R					// title screen level select
#define CONTROL_PAGE_DOWN 	BUTTON_L					// title screen level select

#endif