#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <libdragon.h>

extern joypad_port_t gMainController;
extern bool gControllerFound;

typedef enum {
    BUTTON_A       = 1 << 15,
    BUTTON_B       = 1 << 14,
    BUTTON_Z       = 1 << 13,
    BUTTON_START   = 1 << 12,
    BUTTON_D_UP    = 1 << 11,
    BUTTON_D_DOWN  = 1 << 10,
    BUTTON_D_LEFT  = 1 << 9,
    BUTTON_D_RIGHT = 1 << 8,
    BUTTON_Y       = 1 << 7,
    BUTTON_X       = 1 << 6,
    BUTTON_L       = 1 << 5,
    BUTTON_R       = 1 << 4,
    BUTTON_C_UP    = 1 << 3,
    BUTTON_C_DOWN  = 1 << 2,
    BUTTON_C_LEFT  = 1 << 1,
    BUTTON_C_RIGHT = 1 << 0
} CONT_BUTTON;

void sa_input_init(void);
void sa_input_deinit(void);

bool is_button_down(CONT_BUTTON button);
bool is_button_pressed(CONT_BUTTON button);
bool is_button_released(CONT_BUTTON button);

bool is_button_combo_pressed(CONT_BUTTON buttons);

#endif