#pragma once
#include "Event.h"

class ClickEvent : public Event {
public:
	inline static const std::string CLICK_EVENT = "click_event";

	ClickEvent(int x, int y, int button, int clicks);

	int x;
	int y;
	int button;
	int clicks;
};
