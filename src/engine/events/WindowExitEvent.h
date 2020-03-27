#pragma once
#include "Event.h"

#include <SDL2/SDL_keycode.h>

class WindowExitEvent : public Event {
public:
	inline static const std::string WINDOW_EXIT_EVENT = "winodw_exit_event";

	WindowExitEvent(int window, SDL_Keymod modifiers);

	int wID;
	SDL_Keymod modifiers;
};