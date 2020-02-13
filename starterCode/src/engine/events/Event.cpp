#include "Event.h"

Event::Event(string type, EventDispatcher* source) {
    this->eventType = type;
    this->source = source;
}

string Event::getType() {
    return eventType;
}

EventDispatcher* Event::getSource() {
    return source;
}
