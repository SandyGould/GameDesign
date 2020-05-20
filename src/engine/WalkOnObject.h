#pragma once

#include "CollisionSystem.h"
#include "EnvironmentObject.h"
#include "Game.h"
#include "events/Event.h"

class WalkOnObject : public EnvironmentObject {

public:
	explicit WalkOnObject(std::string id, SDL_Renderer *r = Game::renderer);
	WalkOnObject(std::string id, std::string filepath, SDL_Renderer *r = Game::renderer);
	WalkOnObject(std::string id, int red, int green, int blue, SDL_Renderer *r = Game::renderer);
	explicit WalkOnObject(const DisplayObject& other);

    bool onCollision(std::shared_ptr<DisplayObject> other, CollisionDirection direction1, CollisionDirection direction2) override;

private:
	int collisionWaitTime = 0;
};
