#include "SelectionMenuBase.h"
#include "SelectionMenuOption.h"
#include "../events/KeyDownEvent.h"

#include <iostream>

SelectionMenuBase::SelectionMenuBase() : DisplayObject("selection_menu"){
	this->alpha = 0;

	loadRGBTexture(red, green, blue, width, height, renderer);
}


void SelectionMenuBase::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons){
	DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}

void SelectionMenuBase::draw(AffineTransform& at) {
	DisplayObject::draw(at);
}

void SelectionMenuBase::handleEvent(Event* e){
	if (e->getType() == KeyDownEvent::ESC_DOWN_EVENT){
		alpha = alpha ^ 50;
		for(auto* child: children){
			if(SelectionMenuOption* c = dynamic_cast<SelectionMenuOption*>(child)){
				c->updateAlpha();
			} else{
				child->alpha = child->alpha ^ 100; // assuming the chidren's alpha starts at 0
			}
		}
	}
}