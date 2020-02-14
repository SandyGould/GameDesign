#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include "Event.h"
#include "EventListener.h"

#include <unordered_map>
#include <vector>
#include <string>

class EventListener;
class Event;

class EventDispatcher {
public:
	EventDispatcher();
	virtual ~EventDispatcher();
	
	void addEventListener(EventListener* l, std::string eventType);
	void removeEventListener(EventListener* l, std::string eventType);
	bool hasEventListener(EventListener* l, std::string eventType);
	void dispatchEvent(Event *e);

private:
	
	/* List of listeners */
    std::unordered_map<std::string, std::vector<EventListener*>*> *listeners;


};

#endif