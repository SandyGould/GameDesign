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


	/*mage = new Mage(player);
	mage->position = {400, 400};
	mage->height = 80;
	mage->width = 70;

	allSprites->addChild(mage);
*/
    archer = new Archer(player);
    archer-> position = {200,200};
    archer->height = 80;
    archer->width = 70;

    allSprites->addChild(archer);

	masterArcher = new MasterArcher(player);
    masterArcher-> position = {500,500};
    masterArcher->height = 80;
    masterArcher->width = 70;

    allSprites->addChild(masterArcher);

	roarMonster = new RoarMonster(player);
	roarMonster-> position = {100, 100};
	roarMonster->height = 80;
	roarMonster->width = 70;

	allSprites->addChild(roarMonster);

	knight = new Knight(player);
	knight->position = {200,400};
	knight->height = 80;
	knight->width = 70;

	allSprites->addChild(knight);

	cannoneer = new Cannoneer(player);
	cannoneer->position = {500,100};
	cannoneer->height = 80;
	cannoneer->width = 70;

	allSprites->addChild(cannoneer);

	rubberCannoneer = new RubberCannoneer(player);
	rubberCannoneer->position = {600, 200};
	rubberCannoneer->height=80;
	rubberCannoneer->width=70;

	allSprites->addChild(rubberCannoneer);

	kingdomArcher = new KingdomArcher(player);
	kingdomArcher->position = {400,200};
	kingdomArcher->height= 80;
	kingdomArcher->width=80;

	allSprites->addChild(kingdomArcher);
	
	poisoner = new Poisoner(player);
	poisoner->position = {800,800};
	poisoner->height = 80;
	poisoner->width = 70;

	allSprites->addChild(poisoner);
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
