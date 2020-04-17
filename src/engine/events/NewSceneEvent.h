#pragma once

#include "Event.h"

class NewSceneEvent : public Event {
public:
	inline static const std::string FADE_IN_EVENT = "fade_in_event";
	inline static const std::string FADE_OUT_EVENT = "fade_out_event";

	NewSceneEvent();
};