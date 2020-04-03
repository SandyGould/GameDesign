#pragma once
#include "Event.h"

#include <SDL2/SDL_keycode.h>

class MouseWheelEvent : public Event {
public:
	inline static const std::string MOUSE_WHEEL_EVENT = "mouse_wheel_event";

	MouseWheelEvent(int x, int y, int window);

	int x;
	int y;
	int wID;
};
