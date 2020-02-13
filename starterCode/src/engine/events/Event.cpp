#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include "Event.h"
#include <iostream>

Event::Event(string type, EventDispatcher* source){
    eventType = type;
    source = source;
}

string Event::getType()
{
    return eventType;
}

EventDispatcher * Event::getSource()
{
    return source;
}