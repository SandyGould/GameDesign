#include "WindowExitEvent.h"

WindowExitEvent::WindowExitEvent(int window, SDL_Keymod modifiers) : Event(WindowExitEvent::WINDOW_EXIT_EVENT) {
	this->wID = window;
	this->modifiers = modifiers;
}
