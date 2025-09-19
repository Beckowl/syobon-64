#include "sa_input.h"
#include <libdragon.h>

joypad_port_t gMainController = JOYPAD_PORT_1;
bool gControllerFound = false;

static void find_main_controller() {
    gControllerFound = false;

    for (int i = JOYPAD_PORT_1; i <= JOYPAD_PORT_4; i++) {
        joypad_port_t port = (joypad_port_t)i;

        if (joypad_get_identifier(port) == JOYBUS_IDENTIFIER_N64_CONTROLLER) {
            gMainController = port;
            gControllerFound = true;
            
            break;
        }
    }
}

void sa_input_init(void) {
    joypad_init();
    find_main_controller();
}

void sa_input_deinit(void) {
    joypad_close();
}

bool is_button_pressed(CONT_BUTTON button) {
    if (!gControllerFound) return false;

    joypad_buttons_t pressed= joypad_get_buttons_pressed(gMainController);
    return pressed.raw & button;
}

bool is_button_down(CONT_BUTTON button) {
    if (!gControllerFound) return false;

    joypad_buttons_t held = joypad_get_buttons_held(gMainController);
    return held.raw & button;
}

bool is_button_released(CONT_BUTTON button) {
    if (!gControllerFound) return false;

    joypad_buttons_t released = joypad_get_buttons_released(gMainController);
    return released.raw & button;
}

