#pragma once

#include "../engine/Game.h"
#include "../engine/CollisionSystem.h"

class Rebound : public Game {

public:
	Rebound();
	virtual ~Rebound();

private:
    CollisionSystem* collisionSystem;
};
