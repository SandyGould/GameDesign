#include "MyGame.h"
#include <algorithm>

MyGame::MyGame() : Game(1200, 1000) {
	instance = this;

	//scene = new Scene("scene1");
	//scene->loadScene("./resources/scene/test.json");
	//scene2 = new Scene("scene2");
	//scene2->loadScene("./resources/scene/test2.json");

	camera = new Camera();

	questManager = new QuestManager();

	collect = new Sound();
	collect->setSFX("./resources/sounds/Fruit collect 1.wav");
	
	// move that point to the middle
	camera->position = {600, 500};
	instance->addChild(camera);
	//allSprites->addChild(scene);

	scene = new Scene();
	scene->loadScene("./resources/cameraDemo/loadScene.json");

	camera->addChild(scene);

	player = new Player();
	player->position = {0, 0};
	player->width = player->height = 100;
	player->pivot = {50, 50};
	scene->addChild(player);

	coin = new Coin();
	coin->position = {0, -200};
	coin->width = coin->height = 30;
	coin->pivot = {15, 15};
	scene->addChild(coin);

	coin->addEventListener(questManager, PickedUpEvent::COIN_PICKED_UP);

	// camera = new Camera();
	// camera.x = ( player->position.x + player->getWidth / 2 ) - 1200 / 2;
    // camera.y = ( player->position.y + player->getHeight / 2 ) - 1000 / 2;
}

MyGame::~MyGame() {
	collect->quitSounds();
}


void MyGame::update(std::set<SDL_Scancode> pressedKeys) {
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		if (player->position.x < 120) {
			player->position.x += 2;
			camera->panRight(2);
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		if (player->position.x > -140) {
			player->position.x -= 2;
			camera->panLeft(2);
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		player->position.y += 2;
		camera->panDown(2);
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		player->position.y -= 2;
		camera->panUp(2);
	}

	// to test zoom
	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		camera->zoomIn(.1);
	}
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		camera->zoomOut(.1);
	}

	if (player->position.x - player->pivot.x < coin->position.x - coin->pivot.x + coin->width &&
		player->position.x - player->pivot.x + player->width > coin->position.x - coin->pivot.x &&
		player->position.y - player->pivot.y < coin->position.y - coin->pivot.y + coin->height &&
		player->position.y - player->pivot.y + player-> height > coin->position.y - coin->pivot.y &&
		coin->visible){
			Event* pickUp = new Event(PickedUpEvent::COIN_PICKED_UP, coin);
			collect->playSFX();
			coin->dispatchEvent(pickUp);
			delete pickUp;
			coin->visible = false;
	}
	//if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
	//	if(allSprites->getChild("scene1") != NULL){
	//		allSprites->addChild(scene2);
	//		allSprites->children.erase(std::remove(allSprites->children.begin(), allSprites->children.end(), scene), allSprites->children.end());
	//	}
	//	else if(allSprites->getChild("scene2") != NULL){
	//		allSprites->addChild(scene);
	//		allSprites->children.erase(std::remove(allSprites->children.begin(), allSprites->children.end(), scene2), allSprites->children.end());
	//	}
	//}

	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform& at) {
	Game::draw(at);
}