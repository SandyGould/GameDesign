#include "SelectionMenuOption.h"

#include "../events/GameStartEvent.h"
#include "../events/MouseDownEvent.h"
#include "../events/RestartEvent.h"

#include <iostream>

using namespace std;

SelectionMenuOption::SelectionMenuOption(SelectionMenuBase* base, const string& id, const string& text)
    : DisplayObject(base->id + "_" + id, 255, 255, 255) {
    this->base = base;
	this->text = text;
	this->textbox = std::make_shared<TextBox>(base->id + "_" + text, text);
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
    if (!this->base->active) {
        return;
    }

	if (e->getType() == MouseDownEvent::MOUSE_DOWN_EVENT){
		auto* event = dynamic_cast<MouseDownEvent*>(e);

		if(this->id == base->id + "_" + SelectionMenuOption::QUIT &&
			this->position.x <= event->x && event->x <= this->position.x + this->width &&
			this->position.y <= event->y && event->y <= this->position.y + this->height) {
			exit(0);
		} else if (this->id == base->id + "_" + SelectionMenuOption::RESUME &&
			this->position.x <= event->x && event->x <= this->position.x + this->width &&
			this->position.y <= event->y && event->y <= this->position.y + this->height) {
            Game::instance->paused = false;
            Game::instance->container->removeImmediateChild(this->parent->id);
		} else if (this->id == base->id + "_" + SelectionMenuOption::START &&
			this->position.x <= event->x && event->x <= this->position.x + this->width &&
			this->position.y <= event->y && event->y <= this->position.y + this->height) {
			EventDispatcher::getInstance().dispatchEvent(new Event(GameStartEvent::GAME_START_EVENT));
		}
		else if (this->id == base->id + "_" + SelectionMenuOption::CONTINUE &&
			this->position.x <= event->x && event->x <= this->position.x + this->width &&
			this->position.y <= event->y && event->y <= this->position.y + this->height) {
            Game::instance->paused = false;
			EventDispatcher::getInstance().dispatchEvent(new Event(RestartEvent::RESTART_EVENT));
            Game::instance->container->removeImmediateChild(this->parent->id);
		}
	}
}
