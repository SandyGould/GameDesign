#pragma once

#include "Event.h"

class GameOverEvent : public Event {
public:
	inline static const std::string GAME_OVER_EVENT = "game_over_event";
	GameOverEvent();
};