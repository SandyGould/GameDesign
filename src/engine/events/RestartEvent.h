#pragma once

#include "Event.h"

class RestartEvent : public Event {
public:
	inline static const std::string RESTART_EVENT = "restart_event";
	RestartEvent();
};