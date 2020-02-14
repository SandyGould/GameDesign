#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	instance = this;

	allSprites = new DisplayObjectContainer();
	
	// move that point to the middle
	allSprites->position = {600, 500};
	instance->addChild(allSprites);

	player = new Sprite("player", "./resources/character/Idle_1.png");
	player->position = {0, 0};
	player->width = player->height = 100;
	player->pivot = {50, 50};
	allSprites->addChild(player);

	coin = new Sprite("coin","./resources/solarSystem/Planet.png");
	coin->position = {200, 0};
	coin->width = coin->height = 30;
	coin->pivot = {15, 15};
	allSprites->addChild(coin);
}

MyGame::~MyGame(){
}


void MyGame::update(set<SDL_Scancode> pressedKeys){
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
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

	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}