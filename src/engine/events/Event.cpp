#include "Event.h"

Event::Event(std::string type, EventDispatcher* source) {
    this->eventType = type;
    this->source = source;
}

std::string Event::getType() {
    return eventType;
}

EventDispatcher* Event::getSource() {
    return source;
}
