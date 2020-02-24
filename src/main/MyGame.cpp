#include "MyGame.h"

#include <iostream>

using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	instance = this;
	curScene = new Scene();
	instance->addChild(curScene);
}

MyGame::MyGame(string sceneToLoad) : Game(1200, 1000){
	instance = this;
	curScene = new Scene();

	//To be uncommented when we have actual scenes to load
	//This way is just easier to test for now

	//this->curScene->loadScene(sceneToLoad);
	
	instance->addChild(curScene);
	cout << sceneToLoad << endl;
}

MyGame::~MyGame() {
}

void MyGame::update(std::set<SDL_Scancode> pressedKeys) {
	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform& at) {
	Game::draw(at);
}