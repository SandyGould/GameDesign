#include "SelectionMenuBase.h"
#include "SelectionMenuOption.h"
#include "../events/KeyDownEvent.h"

SelectionMenuBase::SelectionMenuBase() : DisplayObject("selection_menu", 0, 0, 0) {
	this->alpha = 0;
}

void SelectionMenuBase::update(const unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const unordered_set<Uint8>& pressedButtons){
	DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}

void SelectionMenuBase::draw(AffineTransform& at) {
	DisplayObject::draw(at);
}

void SelectionMenuBase::handleEvent(Event* e){
	if (e->getType() == KeyDownEvent::ESC_DOWN_EVENT){
		alpha = alpha ^ 50;
		for(auto child: children){
			if(auto c = dynamic_pointer_cast<SelectionMenuOption>(child)){
				c->updateAlpha();
			} else{
				child->alpha = child->alpha ^ 100; // assuming the chidren's alpha starts at 0
			}
		}
	}
}