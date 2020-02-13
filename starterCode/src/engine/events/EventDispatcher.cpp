#include "EventDispatcher.h"
#include <cmath>

EventDispatcher::EventDispatcher()
{
    listeners = new std::unordered_map<std::string, std::vector<EventListener*>*>();
}

EventDispatcher::~EventDispatcher()
{
    delete listeners;
}

void EventDispatcher::addEventListener(EventListener* l, std::string eventType)
{
    if(listeners->count(eventType ) == 1)
    {
        listeners->at(eventType)->push_back(l);
    }
    else
    {
        std::vector<EventListener*>* newvect = new std::vector<EventListener*>();
        newvect->push_back(l);
        listeners->emplace(eventType,newvect);
    }
}
void EventDispatcher::removeEventListener(EventListener* l, std::string eventType)
{
    int listener_index = 0;
    std::vector<EventListener *>* vl = listeners->at(eventType);
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
bool EventDispatcher::hasEventListener(EventListener* l, std::string eventType)
{
    int listener_index = -1;
    std::vector<EventListener *>* vl = listeners->at(eventType);
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
    std::vector<EventListener *>* vl = listeners->at(e->getType());
    for(int i = 0; i<vl->size(); i++)
    {
        vl->at(i)->handleEvent(e);
    }
}