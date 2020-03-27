#pragma once
#include "Event.h"

#include <SDL2/SDL_keycode.h>

class MouseMotionEvent : public Event {
public:
	inline static const std::string MOUSE_MOTION_EVENT = "mouse_motion_event";

	MouseMotionEvent(int x, int y, int window, SDL_Keymod modifiers);

	int x;
	int y;
	int wID;
	SDL_Keymod modifiers;
};
