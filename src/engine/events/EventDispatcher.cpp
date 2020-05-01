#include "EventDispatcher.h"
#include "DisplayTreeChangeEvent.h"
#include <iostream>

EventDispatcher::EventDispatcher() {}

void EventDispatcher::addEventListener(EventListener* l, std::string eventType) {
    if (listeners.count(eventType) > 0) {
        listeners.at(eventType).push_back(l);
    } else {
        std::vector<EventListener*> newvect{l};
        listeners.emplace(eventType, newvect);
    }
}

void EventDispatcher::removeEventListener(EventListener* l, std::string eventType) {
    int listener_index = 0;
    auto vl = listeners.at(eventType);
    for (size_t i = 0; i < vl.size(); i++) {
        if (vl.at(i) == l) {
            listener_index = i;
            break;
        }
    }
    vl.erase(vl.begin() + listener_index);
}

bool EventDispatcher::hasEventListener(EventListener* l, std::string eventType) {
    int listener_index = -1;
    auto vl = listeners.at(eventType);
    if (listeners.count(eventType) != 1) {
        return false;
    }

    for (size_t i = 0; i < vl.size(); i++) {
        if (vl.at(i) == l) {
            listener_index = i;
            break;
        }
    }

    if (listener_index != -1) {
        return true;
    } else {
        return false;
    }
}

void EventDispatcher::dispatchEvent(Event* e) {
    if (!listeners.count(e->getType())) {
        return;
    }

    for (auto listener : listeners.at(e->getType())) {
        listener->handleEvent(e);
    }
}
