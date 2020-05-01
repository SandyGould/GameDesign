#pragma once

#include "Event.h"

class PlayerDeathEvent : public Event {
public:
    inline static const std::string PLAYER_DEATH_EVENT = "player_death_event";
    PlayerDeathEvent();
};