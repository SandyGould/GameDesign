#include "EventDispatcher.h"

#include <algorithm>

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
    if (listeners.find(eventType) == listeners.cend()) {
        return;
    }

    if (listenersToErase.find(eventType) == listenersToErase.cend()) {
        listenersToErase.try_emplace(eventType, std::queue<EventListener*>({l}));
    } else {
        listenersToErase.at(eventType).push(l);
    }
}

bool EventDispatcher::hasEventListener(EventListener* l, std::string eventType) {
    auto it = listeners.find(eventType);
    if (it == listeners.cend()) {
        return false;
    }

    auto& vl = it->second;
    return std::find(vl.cbegin(), vl.cend(), l) != vl.cend();
}

void EventDispatcher::clear() {
    listeners.clear();
    listenersToErase.clear();
}

void EventDispatcher::dispatchEvent(Event* e) {
    std::string type = e->getType();

    auto it = listeners.find(type);
    if (it == listeners.cend()) {
        return;
    }

    auto& vl = it->second;
    for (auto listener : vl) {
        listener->handleEvent(e);
    }

    if (listenersToErase.find(type) != listenersToErase.cend()) {
        while (!listenersToErase.at(type).empty()) {
            vl.erase(std::find(vl.cbegin(), vl.cend(), listenersToErase.at(type).front()));
            listenersToErase.at(type).pop();
        }
    }
}
