#include "MyGame.h"

MyGame::MyGame() : Game(1200, 1000) {
	instance = this;

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
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end() ) {
		player->position.x += 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		player->position.x -= 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		player->position.y += 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		player->position.y -= 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
		player->alpha -= 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_E) != pressedKeys.end()) {
		player->alpha += 2;
	}

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

	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform& at) {
	Game::draw(at);
}