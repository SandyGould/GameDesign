#ifndef EVENT_H
#define EVENT_H

#include "EventDispatcher.h"

#include <string>

class EventDispatcher;

class Event {
public:
	Event(const std::string& type);
    virtual ~Event() = default;

	std::string getType();
	//EventDispatcher getSource();

private:
	std::string eventType;
	//EventDispatcher source;
};

#endif