#pragma once
#include "Event.h"

class DragStartEvent : public Event {
  public:
    inline static const std::string DRAG_START_EVENT = "drag_start_event";

    DragStartEvent(int x, int y);

    int x;
    int y;
};
