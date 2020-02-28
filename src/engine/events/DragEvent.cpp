#include "DragEvent.h"

DragEvent::DragEvent(EventDispatcher* source, int x, int y) : Event(DragEvent::DRAG_EVENT, source) {
	this->x = x;
	this->y = y;
}
