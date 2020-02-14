#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include "Event.h"
#include "EventDispatcher.h"
#include <vector>

using namespace std;

class Event;
class EventDispatcher;

class EventListener {

public:

	virtual void handleEvent(Event* e) = 0;

private:
};

#endif