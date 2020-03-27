#include "MyGame.h"
#include "math.h"
#include <iostream>

#define HISTORY_SIZE 8

MyGame::MyGame() : Game(1200, 1000) {
	instance = this;

	history = new std::set<SDL_Scancode> [HISTORY_SIZE];

	allSprites = new DisplayObjectContainer();

	questManager = new QuestManager();

	// move that point to the middle
	allSprites->position = {600, 500};
	instance->addChild(allSprites);

	player = new Player();
	player->position = {0, 0};
	player->width = player->height = 100;
	player->pivot = {50, 50};
	allSprites->addChild(player);

	shield = new Shield();
	player->addChild(shield);
	shield->position.x = 110;
	shield->position.y = 0;
	shield->width = 40;
	shield->height = 100;
	shield->pivot = {50, 50};

	coin = new Coin();
	coin->position = {200, 0};
	coin->width = coin->height = 30;
	coin->pivot = {15, 15};
	allSprites->addChild(coin);

	coin->addEventListener(questManager, PickedUpEvent::COIN_PICKED_UP);
}

MyGame::~MyGame() {
}


void MyGame::update(std::set<SDL_Scancode> pressedKeys) {
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

	if (player->position.x - player->pivot.x < coin->position.x - coin->pivot.x + coin->width &&
		  player->position.x - player->pivot.x + player->width > coin->position.x - coin->pivot.x &&
		  player->position.y - player->pivot.y < coin->position.y - coin->pivot.y + coin->height &&
		  player->position.y - player->pivot.y + player-> height > coin->position.y - coin->pivot.y &&
		  coin->visible){
		Event* pickUp = new Event(PickedUpEvent::COIN_PICKED_UP, coin);
		coin->dispatchEvent(pickUp);
		delete pickUp;
		coin->visible = false;
	}

	updateHistory(pressedKeys);

	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform& at) {
	Game::draw(at);
}

void MyGame::updateHistory(std::set<SDL_Scancode> pressedKeys) {
	for (int i = 0; i < HISTORY_SIZE-1; i++) {
		history[i] = history[i+1];
	}
	history[HISTORY_SIZE-1] = pressedKeys;
}

bool MyGame::checkDoubleTaps(SDL_Scancode key) {
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
