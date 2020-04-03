#include "TweenEvent.h"

TweenEvent::TweenEvent(std::string eventType, Tween tween): Event(eventType){}

Tween * TweenEvent::getTween(){
	return NULL;
}