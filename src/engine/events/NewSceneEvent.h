#pragma once

#include "Event.h"

class NewSceneEvent : public Event {
public:
	inline static const std::string IN_SCENE_EVENT = "in_scene_event";
	inline static const std::string OUT_SCENE_EVENT = "out_scene_event";

	NewSceneEvent();
};