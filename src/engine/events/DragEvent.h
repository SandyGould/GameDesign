#pragma once
#include "Event.h"

class DragEvent : public Event {
public:
	inline static const std::string DRAG_EVENT = "drag_event";

	DragEvent(int x, int y, int xrel, int yrel);

	int x;
	int y;
	int xrel;
	int yrel;
};
