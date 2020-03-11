#pragma once
#include "Event.h"

#include <SDL2/SDL_keycode.h>

class MouseDownEvent : public Event {
public:
	inline static const std::string MOUSE_DOWN_EVENT = "mouse_down_event";

	MouseDownEvent(int x, int y, int button, int clicks, int window, SDL_Keymod modifiers);

	int x;
	int y;
	int button;
	int clicks;
	int wID;
	SDL_Keymod modifiers;
};
