#include "ClickEvent.h"

ClickEvent::ClickEvent(EventDispatcher* source, int x, int y, int button, int clicks) : Event(ClickEvent::CLICK_EVENT, source) {
	this->x = x;
	this->y = y;
	this->button = button;
	this->clicks = clicks;
}
