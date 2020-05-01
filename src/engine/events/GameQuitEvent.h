#pragma once

#include "Event.h"

class GameQuitEvent : public Event {
public:
	inline static const std::string GAME_QUIT_EVENT = "game_quit_event";
	GameQuitEvent();
};