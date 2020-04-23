#include "DisplayTreeChangeEvent.h"

DisplayTreeChangeEvent::DisplayTreeChangeEvent(std::shared_ptr<DisplayObject> object, bool added)
    : Event(DisplayTreeChangeEvent::DISPLAY_TREE_CHANGE_EVENT) {
    this->object = object;
    this->added = added;
}