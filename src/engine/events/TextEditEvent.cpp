#include "TextEditEvent.h"


TextEditEvent::TextEditEvent(char* text, int start, int length, int window, SDL_Keymod modifiers) : Event(TextEditEvent::TEXT_EDIT_EVENT) {
    this->text = text;
    this->start = start;
    this->length = length;
    this->wID = window;
    this->modifiers = modifiers;    
}
