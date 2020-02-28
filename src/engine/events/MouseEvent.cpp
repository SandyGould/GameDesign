#include "MouseEvent.h"

MouseEvent::MouseEvent(EventDispatcher* source, int x, int y, int button, int clicks) : Event(MouseEvent::MOUSE_EVENT, source) {
	this->x = x;
	this->y = y;
	this->button = button;
	this->clicks = clicks;
}
