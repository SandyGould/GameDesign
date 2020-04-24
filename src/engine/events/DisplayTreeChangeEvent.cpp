#include "DisplayTreeChangeEvent.h"

DisplayTreeChangeEvent::DisplayTreeChangeEvent(std::weak_ptr<DisplayObject> object, bool added)
    : Event(DisplayTreeChangeEvent::DISPLAY_TREE_CHANGE_EVENT) {
    this->object = object;
    this->added = added;
}
