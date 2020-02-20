#include "MyGame.h"

MyGame::MyGame() : Game(1200, 1000) {
	instance = this;
}

MyGame::~MyGame() {
}


void MyGame::update(std::set<SDL_Scancode> pressedKeys) {
	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform& at) {
	Game::draw(at);
}