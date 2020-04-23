#pragma once

#include "Event.h"

#include "../DisplayObject.h"

class DisplayTreeChangeEvent : public Event {
public:
    inline static const std::string DISPLAY_TREE_CHANGE_EVENT = "display_tree_change_event";

    DisplayTreeChangeEvent(std::shared_ptr<DisplayObject> object, bool added);

    std::shared_ptr<DisplayObject> object;
    bool added;
};
