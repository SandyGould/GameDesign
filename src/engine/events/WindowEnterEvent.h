#pragma once
#include "Event.h"

#include <SDL2/SDL_keycode.h>

class WindowEnterEvent : public Event {
public:
	inline static const std::string WINDOW_ENTER_EVENT = "winodw_enter_event";

	WindowEnterEvent(int window, SDL_Keymod modifiers);

	int wID;
	SDL_Keymod modifiers;
};