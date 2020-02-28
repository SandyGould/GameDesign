#pragma once
#include "Event.h"

class MouseEvent : public Event {
public:
	inline static const std::string MOUSE_EVENT = "mouse_event";

	MouseEvent(EventDispatcher* source, int x, int y, int button, int clicks);

	int x;
	int y;
	int button;
	int clicks;
};
