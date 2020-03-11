#include "MouseMotionEvent.h"

MouseMotionEvent::MouseMotionEvent(int x, int y, int window, SDL_Keymod modifiers) : Event(MouseMotionEvent::MOUSE_MOTION_EVENT) {
    this->x = x;
    this->y = y;
	this->wID = window;
	this->modifiers = modifiers;
}
