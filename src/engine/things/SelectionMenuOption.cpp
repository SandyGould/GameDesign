#include "SelectionMenuOption.h"

#include "../events/MouseDownEvent.h"
#include "../events/GameStartEvent.h"
#include "../events/RestartEvent.h"

#include <iostream>

using namespace std;

SelectionMenuOption::SelectionMenuOption(string id, string text): DisplayObject(id, 255, 255, 255){
	this->text = text;
	this->textbox = std::make_shared<TextBox>(text, text);
	this->textbox->setColor({0,0,0, 255});
	this->textbox->alpha = 100;
	this->alpha = 100;
	this->addChild(this->textbox);

    EventDispatcher::getInstance().addEventListener(this, MouseDownEvent::MOUSE_DOWN_EVENT);
}

SelectionMenuOption::~SelectionMenuOption() {
    EventDispatcher::getInstance().removeEventListener(this, MouseDownEvent::MOUSE_DOWN_EVENT);
}

void SelectionMenuOption::handleEvent(Event* e) {
    if (!Game::instance->container->hasChild(this->parent->shared_from_this())) {
        return;
    }

	if (e->getType() == MouseDownEvent::MOUSE_DOWN_EVENT){
		auto* event = dynamic_cast<MouseDownEvent*>(e);

		if(this->id == SelectionMenuOption::QUIT &&
			this->position.x <= event->x && event->x <= this->position.x + this->width &&
			this->position.y <= event->y && event->y <= this->position.y + this->height) {
			exit(0);
		} else if (this->id == SelectionMenuOption::RESUME &&
			this->position.x <= event->x && event->x <= this->position.x + this->width &&
			this->position.y <= event->y && event->y <= this->position.y + this->height) {
            Game::instance->container->removeImmediateChild(this->parent->id);
		} else if (this->id == SelectionMenuOption::START &&
			this->position.x <= event->x && event->x <= this->position.x + this->width &&
			this->position.y <= event->y && event->y <= this->position.y + this->height) {
			EventDispatcher::getInstance().dispatchEvent(new Event(GameStartEvent::GAME_START_EVENT));
		}
		else if (this->id == SelectionMenuOption::CONTINUE &&
			this->position.x <= event->x && event->x <= this->position.x + this->width &&
			this->position.y <= event->y && event->y <= this->position.y + this->height) {
			EventDispatcher::getInstance().dispatchEvent(new Event(RestartEvent::RESTART_EVENT));
            Game::instance->container->removeImmediateChild(this->parent->id);
		}
	}
}
