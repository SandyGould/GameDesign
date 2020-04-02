#include "Rebound.h"

#include "../engine/events/DisplayTreeChangeEvent.h"

#include <iostream>

using namespace std;

Rebound::Rebound() : Game(1200, 800) {
	cout << "You probably want to be using the editor instead" << endl;

    this->collisionSystem = new CollisionSystem();
    EventDispatcher::getInstance().addEventListener(this->collisionSystem, DisplayTreeChangeEvent::DISPLAY_TREE_CHANGE_EVENT);
}

Rebound::~Rebound() {
}

void Rebound::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
    this->collisionSystem->update();
}
