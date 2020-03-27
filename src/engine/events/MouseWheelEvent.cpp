#include "MouseWheelEvent.h"


MouseWheelEvent::MouseWheelEvent(int x, int y, int window) : Event(MouseWheelEvent::MOUSE_WHEEL_EVENT) {
    this->x = x;
    this->y = y;
    this->wID = window;    
}
