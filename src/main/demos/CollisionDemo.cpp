#include "CollisionDemo.h"

#include "../../engine/events/DisplayTreeChangeEvent.h"

#include <iostream>

using namespace std;

CollisionDemo::CollisionDemo() : Game(1200, 800) {
    instance = this;

    this->collisionSystem = new CollisionSystem();
    EventDispatcher::getInstance().addEventListener(this->collisionSystem, DisplayTreeChangeEvent::DISPLAY_TREE_CHANGE_EVENT);

    this->camera = new Camera();
    this->camera->position = {this->windowWidth / 2, this->windowHeight / 2};
    this->camera->pivot = {this->windowWidth / 2, this->windowHeight / 2};
    instance->addChild(this->camera);

    this->scene = new Scene();
    this->scene->loadScene("./resources/cameraDemo/loadScene.json");

    camera->addChild(this->scene);

    this->moon = new Coin();
    this->moon->position = {this->windowWidth / 2, this->windowHeight / 2};
    this->moon->width = this->moon->height = 100;
    this->moon->pivot = {50, 50};
    this->scene->getChild(0)->addChild(this->moon);

    this->coin = new Coin();
    this->coin->position = {this->windowWidth / 2 + 100, this->windowHeight / 2 + 100};
    this->coin->width = this->coin->height = 30;
    this->coin->pivot = {15, 15};
    this->scene->getChild(0)->addChild(this->coin);

    this->collisionSystem->watchForCollisions("coin", "coin");
}

CollisionDemo::~CollisionDemo() {
}

void CollisionDemo::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
    if (pressedKeys.find(SDL_SCANCODE_I) != pressedKeys.end()) {
        this->moon->position.y -= 5;
    }

    if (pressedKeys.find(SDL_SCANCODE_J) != pressedKeys.end()) {
        this->moon->position.x -= 5;
    }

    if (pressedKeys.find(SDL_SCANCODE_K) != pressedKeys.end()) {
        this->moon->position.y += 5;
    }

    if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end()) {
        this->moon->position.x += 5;
    }

    if (pressedKeys.find(SDL_SCANCODE_O) != pressedKeys.end()) {
        this->moon->rotation -= 0.0314159265;
    }

    if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
        this->moon->rotation += 0.0314159265;
    }

    if (pressedKeys.find(SDL_SCANCODE_N) != pressedKeys.end()) {
        this->moon->scaleX -= 0.1;
        this->moon->scaleY -= 0.1;
    }

    if (pressedKeys.find(SDL_SCANCODE_M) != pressedKeys.end()) {
        this->moon->scaleX += 0.1;
        this->moon->scaleY += 0.1;
    }

    if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
        this->coin->position.y -= 5;
    }

    if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
        this->coin->position.x -= 5;
    }

    if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
        this->coin->position.y += 5;
    }

    if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
        this->coin->position.x += 5;
    }

    if (pressedKeys.find(SDL_SCANCODE_X) != pressedKeys.end()) {
        this->coin->rotation -= 0.0314159265;
    }

    if (pressedKeys.find(SDL_SCANCODE_C) != pressedKeys.end()) {
        this->coin->rotation += 0.0314159265;
    }

    if (pressedKeys.find(SDL_SCANCODE_V) != pressedKeys.end()) {
        this->coin->scaleX -= 0.1;
        this->coin->scaleY -= 0.1;
    }

    if (pressedKeys.find(SDL_SCANCODE_B) != pressedKeys.end()) {
        this->coin->scaleX += 0.1;
        this->coin->scaleY += 0.1;
    }

    // Check for collisions after we finalize ideal positions
    this->collisionSystem->update();
    Game::update(pressedKeys, joystickState, pressedButtons);
}

void CollisionDemo::draw(AffineTransform& at) {
    Game::draw(at);
}

void CollisionDemo::draw_post() {
    SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    this->coin->drawHitbox();
    this->moon->drawHitbox();
}
