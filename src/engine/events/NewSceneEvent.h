#pragma once

#include "Event.h"

class NewSceneEvent : public Event {
public:
	inline static const std::string FADE_IN_EVENT = "fade_in_event";
	inline static const std::string FADE_OUT_EVENT = "fade_out_event";
	inline static const std::string DELETE_EVENT = "delete_event";
	inline static const std::string LOAD_EVENT = "load_event";
	inline static const std::string SCALE_OUT_EVENT = "scale_out_event";
	inline static const std::string SCALE_IN_EVENT = "scale_in_event";
	NewSceneEvent();
};