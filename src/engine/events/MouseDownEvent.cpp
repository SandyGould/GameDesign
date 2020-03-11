#include "MouseDownEvent.h"

MouseDownEvent::MouseDownEvent(int x, int y, int button, int clicks, int window, SDL_Keymod modifiers) : Event(MouseDownEvent::MOUSE_DOWN_EVENT) {
	this->x = x;
	this->y = y;
	this->button = button;
	this->clicks = clicks;
	this->wID = window;
	this->modifiers = modifiers;
}
