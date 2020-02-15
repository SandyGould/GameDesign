#pragma once
#include "Event.h"

#include <string>

class PickedUpEvent : public Event {
public:
	inline static const std::string COIN_PICKED_UP = "coin_picked_up";
};
