#pragma once

#include "Event.h"

class KeyDownEvent : public Event {
public:
	inline static const std::string KEY_DOWN_EVENT = "key_down_event";

	KeyDownEvent();
};