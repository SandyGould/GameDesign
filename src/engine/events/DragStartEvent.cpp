#include "DragStartEvent.h"

DragStartEvent::DragStartEvent(int x, int y) : Event(DragStartEvent::DRAG_START_EVENT) {
    this->x = x;
    this->y = y;
}
