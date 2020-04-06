#include "Rebound.h"
#include "../engine/events/DisplayTreeChangeEvent.h"
#include <iostream>

using namespace std;

Rebound::Rebound() : Game(1200, 800) {
	cout << "Launching Rebound" << endl;
    instance = this;

    this->collisionSystem = new CollisionSystem();
    EventDispatcher::getInstance().addEventListener(this->collisionSystem, DisplayTreeChangeEvent::DISPLAY_TREE_CHANGE_EVENT);

	allSprites = new DisplayObject("allSprites");

	questManager = new QuestManager();

	// move that point to the middle
	allSprites->position = {200, 100};
	instance->addChild(allSprites);

	player = new Player();
	player->position = {0, 0};
	player->width = 110;
	player->height = 80;
	player->pivot = {50, 50};
	player->play("Idle");
	allSprites->addChild(player);

	mage = new Mage();
	mage->position = {400, 400};
	mage->height = 80;
	mage->width = 70;

	allSprites->addChild(mage);
}

Rebound::~Rebound() {
}

void Rebound::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
    this->collisionSystem->update();

	//Mage Attacking
	if (mage->ready == 300) {
		mageAttack = mage->attack(player);
		allSprites->addChild(mageAttack);
	} else if (mage->ready < 240 && mage->ready > 0) {
		mageAttack->position.x += mageAttack->distX;
		mageAttack->position.y += mageAttack->distY;
	} else if (mage->ready == 0) {
		mage->ready = 301;
	}
	mage->ready -= 1;

	// updateHistory(pressedKeys);

	Game::update(pressedKeys, joystickState, pressedButtons);
}

void Rebound::draw(AffineTransform& at) {
	Game::draw(at);
}
