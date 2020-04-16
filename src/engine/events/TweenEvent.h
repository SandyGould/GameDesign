#ifndef TWEENEVENT_H
#define TWEENEVENT_H

#include "../tweens/Tween.h"
#include "Event.h"

#include <string>

// Extends Event and represents progress or completion of a Tween.

class TweenEvent : public Event { 

public:

	inline static const std::string TWEEN_COMPLETE_EVENT = "tween_complete_event";
	inline static const std::string TWEEN_START_EVENT = "tween_start_event";
	inline static const std::string TWEEN_UPDATE_EVENT = "tween_update_event";
    
    TweenEvent(std::string eventType, Tween* tween);
    Tween * getTween();
    std::string getEventType();

private:
	Tween * tween;
	std::string eventType;
};

#endif