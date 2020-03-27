#include "TweenEvent.h"

TweenEvent::TweenEvent(std::string eventType, Tween tween): Event(eventType, NULL){}

Tween * TweenEvent::getTween(){
	return NULL;
}