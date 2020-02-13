#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include "EventDispatcher.h"
#include <iostream>

EventDispatcher::EventDispatcher()
{
    listeners = new std::unordered_map<std::string, std::vector<EventListener*>*>();
}

EventDispatcher::~EventDispatcher()
{
    delete listeners;
}

void EventDispatcher::addEventListener(EventListener* l, string eventType)
{
    if(listeners->count(eventType ) == 1)
    {
        listeners->at(eventType)->push_back(l);
    }
    else
    {
        vector<EventListener*>* newvect = new vector<EventListener*>();
        newvect->push_back(l);
        listeners->emplace(eventType,newvect);
    }
}
void EventDispatcher::removeEventListener(EventListener* l, string eventType)
{
    int listener_index = 0;
    vector<EventListener *>* vl = listeners->at(eventType);
    for(int i = 0; i<vl->size(); i++)
    {
        if(vl->at(i) == l)
        {
            listener_index = i;
            break;
        }
    }
    vl->erase(vl->begin()+listener_index);
}
bool EventDispatcher::hasEventListener(EventListener* l, string eventType)
{
    int listener_index = -1;
    vector<EventListener *>* vl = listeners->at(eventType);
    if(listeners->count(eventType) != 1)
    {
        return false;
    }
    for(int i = 0; i<vl->size(); i++)
    {
        if(vl->at(i) == l)
        {
            listener_index = i;
            break;
        }
    }
    if(listener_index != -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void EventDispatcher::dispatchEvent(Event *e)
{
    vector<EventListener *>* vl = listeners->at(e->getType());
    for(int i = 0; i<vl->size(); i++)
    {
        vl->at(i)->handleEvent(e);
    }
}