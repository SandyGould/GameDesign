#include "MouseUpEvent.h"

MouseUpEvent::MouseUpEvent(int x, int y, int button, int clicks, SDL_Keymod modifiers) : Event(MouseUpEvent::MOUSE_UP_EVENT) {
	this->x = x;
	this->y = y;
	this->button = button;
	this->clicks = clicks;
	this->modifiers = modifiers;
}
