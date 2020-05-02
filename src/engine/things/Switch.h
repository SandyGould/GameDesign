#pragma once

#include "../events/Event.h"

#include "../EnvironmentObject.h"
#include "../DisplayObject.h"
#include "../Game.h"
#include "../AffineTransform.h"


class Switch : public EnvironmentObject {

public:
	Switch(SDL_Renderer *r = Game::renderer);
	~Switch() override;

	void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
	void draw(AffineTransform& at) override;

	bool onCollision(std::shared_ptr<DisplayObject> other) override;
    std::vector<std::shared_ptr<DisplayObject>> temp_children;
	// AffineTransform at = NULL;

private:
    std::string state_on = "";
	std::string state_off = "";
    bool state = false;
};