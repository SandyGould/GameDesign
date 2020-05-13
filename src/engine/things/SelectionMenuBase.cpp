#include "SelectionMenuBase.h"

#include "../Game.h"

SelectionMenuBase::SelectionMenuBase() : DisplayObject("selection_menu", 0, 0, 0) {
	this->alpha = 50;
}

SelectionMenuBase::SelectionMenuBase(const std::string& id) : DisplayObject("selection_menu_" + id, 0, 0, 0) {
    this->alpha = 50;
}

void SelectionMenuBase::update(const unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const unordered_set<Uint8>& pressedButtons) {
    this->active = this->parent == Game::instance->container.get();
    DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}
