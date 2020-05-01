#include "EventDispatcher.h"

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

    listenersToErase.push(l);
}

bool EventDispatcher::hasEventListener(EventListener* l, std::string eventType) {
    auto it = listeners.find(eventType);
    if (it == listeners.cend()) {
        return false;
    }

    auto vl = it->second;
    return std::find(vl.cbegin(), vl.cend(), l) != vl.cend();
}

void EventDispatcher::dispatchEvent(Event* e) {
    if (!listeners.count(e->getType())) {
        return;
    }

    for (auto listener : listeners.at(e->getType())) {
        listener->handleEvent(e);
    }

    while (!listenersToErase.empty()) {
        listeners.at(e->getType()).erase(std::find(listeners.at(e->getType()).begin(), listeners.at(e->getType()).end(), listenersToErase.front()));
        listenersToErase.pop();
    }
}
