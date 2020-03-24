#pragma once
#include "Event.h"

#include <SDL2/SDL_keycode.h>

class TextEditEvent : public Event {
public:
	inline static const std::string TEXT_EDIT_EVENT = "text_edit_event";

	TextEditEvent(char* text, int start, int length, int window, SDL_Keymod modifiers);

    char* text;
    int start;
    int length;
	int wID;
	SDL_Keymod modifiers;
};