#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include "Event.h"
#include "EventListener.h"

#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

class EventListener;
class Event;


// Singleton design pattern
// Hopefully I won't regret this later...
// https://stackoverflow.com/a/1008289/5661593
class EventDispatcher {
public:
    static EventDispatcher& getInstance() {
        static EventDispatcher instance;
        return instance;
    }

    EventDispatcher(EventDispatcher const& other) = delete;
    void operator=(EventDispatcher const& other) = delete;

	void addEventListener(EventListener* l, std::string eventType);
	void removeEventListener(EventListener* l, std::string eventType);
	bool hasEventListener(EventListener* l, std::string eventType);
    void clear();
	void dispatchEvent(Event *e);

private:
    EventDispatcher();

    /* List of listeners */
	std::unordered_map<std::string, std::vector<EventListener*>> listeners;

    std::queue<EventListener*> listenersToErase;
};

#endif