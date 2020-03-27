#include "TextInputEvent.h"

TextInputEvent::TextInputEvent(char* text, int window, SDL_Keymod modifiers) : Event(TextInputEvent::TEXT_INPUT_EVENT) {
    this->text = text;
    this->wID = window;
    this->modifiers = modifiers;
}
