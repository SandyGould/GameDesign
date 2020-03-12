#include "DragEvent.h"

DragEvent::DragEvent(int x, int y, int xrel, int yrel, int window, SDL_Keymod modifiers) : Event(DragEvent::DRAG_EVENT) {
	this->x = x;
	this->y = y;
	this->xrel = xrel;
	this->yrel = yrel;
	this->wID = window;
    this->modifiers = modifiers;
}
