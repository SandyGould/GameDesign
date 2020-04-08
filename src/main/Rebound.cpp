#include "Rebound.h"
#include "../engine/events/DisplayTreeChangeEvent.h"
#include <iostream>

using namespace std;

#define HISTORY_SIZE 8

Rebound::Rebound() : Game(1200, 800) {
	cout << "Launching Rebound" << endl;
    instance = this;

    this->collisionSystem = new CollisionSystem();
    EventDispatcher::getInstance().addEventListener(this->collisionSystem, DisplayTreeChangeEvent::DISPLAY_TREE_CHANGE_EVENT);

	history = new std::unordered_set<SDL_Scancode> [HISTORY_SIZE];

	allSprites = new DisplayObject("allSprites");

	questManager = new QuestManager();

	// move that point to the middle
	allSprites->position = {200, 100};
	instance->addChild(allSprites);

	player = new Player();
	player->position = {0, 0};
	player->width = player->height = 100;
	player->pivot = {50, 50};
	player->play("Idle");
	allSprites->addChild(player);


	mage = new Mage();
	mage->position = {400, 400};
	mage->height = 80;
	mage->width = 70;

	allSprites->addChild(mage);

    archer = new Archer(player);
    archer-> position = {200,200};
    archer->height = 80;
    archer->width = 70;

    allSprites->addChild(archer);
}

Rebound::~Rebound() {
}

void Rebound::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
    this->collisionSystem->update();
	// CHARACTER MOVEMENT
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		if (checkDoubleTaps(SDL_SCANCODE_RIGHT)) {
			player->position.x += 20;
			player->changeStamina(-100);
		} else {
			player->position.x += 4;
			player->changeStamina(-3);
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		if (checkDoubleTaps(SDL_SCANCODE_LEFT)) {
			player->position.x -= 20;
			player->changeStamina(-100);
		} else {
			player->position.x -= 4;
			player->changeStamina(-3);
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		if (checkDoubleTaps(SDL_SCANCODE_DOWN)) {
			player->position.y += 20;
			player->changeStamina(-100);
		} else {
			player->position.y += 4;
			player->changeStamina(-3);
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		if (checkDoubleTaps(SDL_SCANCODE_UP)) {
			player->position.y -= 20;
			player->changeStamina(-100);
		} else {
			player->position.y -= 4;
			player->changeStamina(-3);
		}
	}

	// SHIELD CONTROLS
	if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) {
		shield->position.x = 110;
		shield->position.y = 0;
		shield->rotation = 0;
		player->changeStamina(-2);
	}
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		shield->position.x = -50;
		shield->position.y = 0;
		shield->rotation = 0;
		player->changeStamina(-2);
	}
	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		shield->position.x = 0;
		shield->position.y = 100;
		shield->rotation = M_PI/2;
		player->changeStamina(-2);
	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		shield->position.x = 0;
		shield->position.y = -100;
		shield->rotation = -M_PI/2;
		player->changeStamina(-2);
	}

	// STAMINA REFRESH
	player->changeStamina(2);

	//Mage Attacking
	if (mage->ready == 300) {
		mageAttack = mage->attack(player);
		allSprites->addChild(mageAttack);
	} else if (mage->ready < 240 && mage->ready > 0) {
		mageAttack->position.x += mageAttack->distX;
		mageAttack->position.y += mageAttack->distY;
	} else if (mage->ready == 0) {
		// allSprites->removeImmediateChild(mageAttack);
		mage->ready = 301;
	}
	mage->ready -= 1;

	updateHistory(pressedKeys);

	Game::update(pressedKeys, joystickState, pressedButtons);
}

void Rebound::draw(AffineTransform& at) {
	Game::draw(at);
}

void Rebound::updateHistory(std::unordered_set<SDL_Scancode> pressedKeys) {
	for (int i = 0; i < HISTORY_SIZE-1; i++) {
		history[i] = history[i+1];
	}
	history[HISTORY_SIZE-1] = pressedKeys;
}

bool Rebound::checkDoubleTaps(SDL_Scancode key) {
	for (int i = HISTORY_SIZE-1; i >= 1; i--) {
		if (history[i].find(key) == history[i].end()) {
			for (int k = i-1; k >= 0; k--) {
				if (history[k].find(key) != history[k].end()) {
					return true;
				}
			}
		}
	}
	return false;
}
