#pragma once

#include "events/EventListener.h"

class QuestManager : public EventListener {
public:
	void handleEvent(Event* e) override;
};