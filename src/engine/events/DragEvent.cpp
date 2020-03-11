#include "DragEvent.h"

DragEvent::DragEvent(int x, int y, int xrel, int yrel, int window) : Event(DragEvent::DRAG_EVENT) {
	this->x = x;
	this->y = y;
	this->xrel = xrel;
	this->yrel = yrel;
	this->wID = window;
}
