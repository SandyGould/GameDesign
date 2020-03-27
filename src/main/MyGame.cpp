#include "MyGame.h"
#include "math.h"

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
		player->position.x += 4;
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		player->position.x -= 4;
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		player->position.y += 4;
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		player->position.y -= 4;
	}
	// SHIELD CONTROLS
	if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) {
		shield->position.x = 110;
		shield->position.y = 0;
		shield->rotation = 0;
	}
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		shield->position.x = -50;
		shield->position.y = 0;
		shield->rotation = 0;
	}
	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		shield->position.x = 0;
		shield->position.y = 100;
		shield->rotation = M_PI/2;
	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		shield->position.x = 0;
		shield->position.y = -100;
		shield->rotation = -M_PI/2;
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
