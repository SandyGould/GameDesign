#pragma once
#include "Event.h"

#include <SDL2/SDL_keycode.h>

class MouseUpEvent : public Event {
public:
	inline static const std::string MOUSE_UP_EVENT = "mouse_up_event";

	MouseUpEvent(int x, int y, int button, int clicks, int window, SDL_Keymod modifiers);

	int x;
	int y;
	int button;
	int clicks;
	int wID;
	SDL_Keymod modifiers;
};
