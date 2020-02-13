#pragma once
#include "Event.h"

using namespace std;

class PickedUpEvent : public Event {
public:
	inline static const string COIN_PICKED_UP = "coin_picked_up";
};
