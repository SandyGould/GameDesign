#include "WindowEnterEvent.h"

WindowEnterEvent::WindowEnterEvent(int window, SDL_Keymod modifiers) : Event(WindowEnterEvent::WINDOW_ENTER_EVENT) {
	this->wID = window;
	this->modifiers = modifiers;
}
