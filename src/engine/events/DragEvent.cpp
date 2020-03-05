#include "DragEvent.h"

DragEvent::DragEvent(int x, int y, int xrel, int yrel) : Event(DragEvent::DRAG_EVENT) {
	this->x = x;
	this->y = y;
	this->xrel = xrel;
	this->yrel = yrel;
}
