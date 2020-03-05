#include "ClickEvent.h"

ClickEvent::ClickEvent(int x, int y, int button, int clicks) : Event(ClickEvent::CLICK_EVENT) {
	this->x = x;
	this->y = y;
	this->button = button;
	this->clicks = clicks;
}
