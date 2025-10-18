#ifndef MESSAGE_BOX_H
#define MESSAGE_BOX_H

#include "message_text.hpp"

extern bool gMessageBoxActive;

void message_box_open(TextMessageId messageId);
void message_box_draw(void);
bool message_box_update(void);
void message_box_reset(void);

#endif