#pragma once
#include "Event.h"

#include <SDL2/SDL_keycode.h>

class TextInputEvent : public Event {
public:
	inline static const std::string TEXT_INPUT_EVENT = "text_input_event";

	TextInputEvent(char* text, int window, SDL_Keymod modifiers);

    char* text;
	int wID;
	SDL_Keymod modifiers;
};