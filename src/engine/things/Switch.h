#pragma once

#include "../CollisionSystem.h"
#include "../EnvironmentObject.h"

class Switch : public EnvironmentObject {

public:
	explicit Switch(const std::string& id, SDL_Renderer* r = Game::renderer);

    bool onCollision(std::shared_ptr<DisplayObject> other, CollisionDirection direction1, CollisionDirection direction2) override;

private:
    std::string state_on = "";
	std::string state_off = "";
    bool state = false;
};
