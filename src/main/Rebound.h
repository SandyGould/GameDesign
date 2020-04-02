#pragma once

#include "../engine/Game.h"
#include "../engine/CollisionSystem.h"

class Rebound : public Game {

public:
	Rebound();
	~Rebound() override;

private:
    CollisionSystem* collisionSystem;
    void update(unordered_set<SDL_Scancode> pressedKeys, jState joystickState, unordered_set<Uint8> pressedButtons) override;
};
