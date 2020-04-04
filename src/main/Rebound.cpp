#include "Rebound.h"

#include "../engine/events/DisplayTreeChangeEvent.h"

#include <iostream>

using namespace std;

Rebound::Rebound() : Game(1200, 800) {
	cout << "You probably want to be using the editor instead" << endl;

    instance = this;

    this->collisionSystem = new CollisionSystem();
    EventDispatcher::getInstance().addEventListener(this->collisionSystem, DisplayTreeChangeEvent::DISPLAY_TREE_CHANGE_EVENT);

	allSprites = new DisplayObject("allSprites");

	// move that point to the middle
	allSprites->position = {200, 100};
	instance->addChild(allSprites);

	player = new Player();
	player->position = {0, 0};
	player->width = player->height = 100;
	player->pivot = {50, 50};
	player->play("Idle");
	allSprites->addChild(player);


	mage = new Archer();
	mage->position = {400, 400};
	mage->height = 80;
	mage->width = 70;

	allSprites->addChild(mage);
}

Rebound::~Rebound() {
}

void Rebound::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
    this->collisionSystem->update();
}
