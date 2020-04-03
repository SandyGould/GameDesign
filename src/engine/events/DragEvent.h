#pragma once
#include "Event.h"

#include <SDL2/SDL_keycode.h>

class DragEvent : public Event {
public:
    inline static const std::string DRAG_EVENT = "drag_event";

    DragEvent(int x, int y, int xrel, int yrel, int window, SDL_Keymod modifiers);

    int x;
    int y;
    int xrel;
    int yrel;
    int wID;
    SDL_Keymod modifiers;
};
