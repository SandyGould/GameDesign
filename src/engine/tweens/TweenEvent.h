#ifndef TWEENEVENT_H
#define TWEENEVENT_H

#include "Tween.h"
#include "../events/Event.h"

#include <string>

// Extends Event and represents progress or completion of a Tween.

class TweenEvent : public Event { 

public:
	enum tween_events { 
		TWEEN_COMPLETE_EVENT // think we have to add some others but idk what they are lol
	};
    
    TweenEvent(std::string eventType, Tween tween);
    Tween * getTween();
};

#endif