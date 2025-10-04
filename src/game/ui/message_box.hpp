#ifndef MESSAGE_BOX_H
#define MESSAGE_BOX_H

#include "text/message_text.hpp"

extern bool gMessageBoxActive;

void message_box_open(TextMessageId messageId);
void message_box_draw(void);
void message_box_update(void);

#endif