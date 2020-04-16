#include "Rooms.h"
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

Rooms::Rooms() : Game(600, 500) {
	
	instance = this;

	camera = new Camera();

	// move that point to the middle
	camera->position = {200, 100};
	camera->pivot = {200, 100};

	instance->addChild(camera);

	// set camera limits (so it doesn't go off map)
	camera->setTopLimit(0);
	camera->setLeftLimit(200);
	camera->setRightLimit(810);
    camera->setBottomLimit(0);

	scene = new Scene();
	scene->loadScene("./resources/Rebound/area1/area1map.json");

	camera->addChild(scene);

	player = new Player();
	player->position = {200, 250};
	player->width = player->height = 50;
	player->pivot = {50, 50};
	scene->addChild(player);

    juggler = juggler->getInstance();

	player_tween = new Tween(player);

    player_tween->animate(TweenableParams::SCALE_X, 5.0, 1.0, 100);
	player_tween->animate(TweenableParams::SCALE_Y, 5.0, 1.0, 100);
	player_tween->animate(TweenableParams::ALPHA, 0, 255, 100);

    juggler->getInstance()->add(player_tween);
}

Rooms::~Rooms() {
}


void Rooms::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		player->position.x += 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
        if (player->position.x > 50) {
            player->position.x -= 2;
        }
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		player->position.y += 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		player->position.y -= 2;
	}
	camera->follow(player->position.x, player->position.y);

	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		camera->zoomIn(1.1);
	}
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		camera->zoomOut(1.1);
	}

	if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
		camera->zoomIn(1.1);
	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		camera->zoomOut(1.1);
	}
    juggler->nextFrame();
	Game::update(pressedKeys, joystickState, pressedButtons);
}

void Rooms::draw(AffineTransform& at) {
	Game::draw(at);
}