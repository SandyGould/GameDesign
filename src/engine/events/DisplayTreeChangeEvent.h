#pragma once

#include "Event.h"

#include "../DisplayObject.h"

class DisplayTreeChangeEvent : public Event {
public:
    inline static const std::string DISPLAY_TREE_CHANGE_EVENT = "display_tree_change_event";

    DisplayTreeChangeEvent(DisplayObject* object, bool added);

    DisplayObject* object;
    bool added;
};
