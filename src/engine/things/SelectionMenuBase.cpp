#include "SelectionMenuBase.h"

SelectionMenuBase::SelectionMenuBase() : DisplayObject("selection_menu", 0, 0, 0) {
	this->alpha = 50;
}

SelectionMenuBase::SelectionMenuBase(const std::string& id) : DisplayObject("selection_menu_" + id, 0, 0, 0) {
    this->alpha = 50;
}
