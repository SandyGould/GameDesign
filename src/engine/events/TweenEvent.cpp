#include "TweenEvent.h"

TweenEvent::TweenEvent(std::string eventType, Tween* tween): Event(eventType){
	this->tween = tween;
	this->eventType = eventType;
}

Tween * TweenEvent::getTween(){
	return this->tween;
}

std::string TweenEvent::getEventType(){
	return this->eventType;
}