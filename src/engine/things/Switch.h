#pragma once

#include "../AffineTransform.h"
#include "../CollisionSystem.h"
#include "../DisplayObject.h"
#include "../EnvironmentObject.h"
#include "../Game.h"
#include "../events/Event.h"

class Switch : public EnvironmentObject {

public:
	Switch(const std::string& id, SDL_Renderer* r = Game::renderer);
	~Switch() override;

	void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
	void draw(AffineTransform& at) override;

    bool onCollision(std::shared_ptr<DisplayObject> other, CollisionDirection direction1, CollisionDirection direction2) override;
    std::vector<std::shared_ptr<DisplayObject>> temp_children;

private:
    std::string state_on = "";
	std::string state_off = "";
    bool state = false;
};