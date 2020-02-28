#include "DragEvent.h"

DragEvent::DragEvent(EventDispatcher* source, int x, int y, int xrel, int yrel) : Event(DragEvent::DRAG_EVENT, source) {
	this->x = x;
	this->y = y;
	this->xrel = xrel;
	this->yrel = yrel;
}
