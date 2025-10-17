#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <libdragon.h>

extern joypad_port_t gMainController;
extern bool gControllerFound;

#define BUTTON_A       (1 << 15)
#define BUTTON_B       (1 << 14)
#define BUTTON_Z       (1 << 13)
#define BUTTON_START   (1 << 12)
#define BUTTON_D_UP    (1 << 11)
#define BUTTON_D_DOWN  (1 << 10)
#define BUTTON_D_LEFT  (1 << 9)
#define BUTTON_D_RIGHT (1 << 8)
#define BUTTON_Y       (1 << 7)
#define BUTTON_X       (1 << 6)
#define BUTTON_L       (1 << 5)
#define BUTTON_R       (1 << 4)
#define BUTTON_C_UP    (1 << 3)
#define BUTTON_C_DOWN  (1 << 2)
#define BUTTON_C_LEFT  (1 << 1)
#define BUTTON_C_RIGHT (1 << 0)
#define BUTTON_NONE    0
#define BUTTON_ALL     0xFFFFFF

void sa_input_init(void);

bool is_button_down(uint16_t button);
bool is_button_pressed(uint16_t button);
bool is_button_released(uint16_t button);

bool is_button_combo_pressed(uint16_t buttons);

#endif