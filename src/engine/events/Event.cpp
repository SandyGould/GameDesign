#include "Event.h"

Event::Event(const std::string& type) {
    this->eventType = type;
    //this->source = source;
}

std::string Event::getType() {
    return eventType;
}

//EventDispatcher Event::getSource() {
//    return source;
//}
