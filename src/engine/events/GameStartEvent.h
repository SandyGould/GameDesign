#pragma once

#include "Event.h"

class GameStartEvent : public Event {
public:
	inline static const std::string GAME_START_EVENT = "game_start_event";
	GameStartEvent();
};