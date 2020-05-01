#include "SelectionMenuOption.h"

#include "../events/MouseDownEvent.h"
#include "../events/KeyDownEvent.h"
#include "../events/GameStartEvent.h"
#include "../events/GameOverEvent.h"
#include "../events/RestartEvent.h"

#include <iostream>

using namespace std;

SelectionMenuOption::SelectionMenuOption(string id, string text): DisplayObject(id, 255, 255, 255){
	this->text = text;
	this->textbox = std::make_shared<TextBox>(text, text);
	this->textbox->setColor({0,0,0, 255});
	this->textbox->alpha = 0;
	this->alpha = 0;
	this->addChild(this->textbox);
}

void SelectionMenuOption::updateAlpha(){
	alpha = alpha ^ 100;
	textbox->alpha  = textbox->alpha ^ 100;
}

void SelectionMenuOption::update(const unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const unordered_set<Uint8>& pressedButtons){
	DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}

void SelectionMenuOption::draw(AffineTransform& at) {
	DisplayObject::draw(at);
}

void SelectionMenuOption::handleEvent(Event* e){
	if (e->getType() == MouseDownEvent::MOUSE_DOWN_EVENT){
		MouseDownEvent* event = static_cast<MouseDownEvent*>(e);

		if(this->id == SelectionMenuOption::QUIT && this->alpha == 100 &&
			this->position.x <= event->x && event->x <= this->position.x + this->width &&
			this->position.y <= event->y && event->y <= this->position.y + this->height){
			exit(0);
		} else if (this->id == SelectionMenuOption::RESUME && this->alpha == 100 &&
			this->position.x <= event->x && event->x <= this->position.x + this->width &&
			this->position.y <= event->y && event->y <= this->position.y + this->height){
			EventDispatcher::getInstance().dispatchEvent(new Event(KeyDownEvent::ESC_DOWN_EVENT));
		} else if (this->id == SelectionMenuOption::START && this->alpha == 100 &&
			this->position.x <= event->x && event->x <= this->position.x + this->width &&
			this->position.y <= event->y && event->y <= this->position.y + this->height){
			EventDispatcher::getInstance().dispatchEvent(new Event(GameStartEvent::GAME_START_EVENT));
		}
		else if (this->id == SelectionMenuOption::CONTINUE && this->alpha == 100 &&
			this->position.x <= event->x && event->x <= this->position.x + this->width &&
			this->position.y <= event->y && event->y <= this->position.y + this->height){
			EventDispatcher::getInstance().dispatchEvent(new Event(RestartEvent::RESTART_EVENT));
		}
	}
	
}