#pragma once

#include "events/Event.h"

#include "EnvironmentObject.h"
#include "Game.h"

class WalkOnObject : public EnvironmentObject {

public:
	explicit WalkOnObject(std::string id, SDL_Renderer *r = Game::renderer);
	WalkOnObject(std::string id, std::string filepath, SDL_Renderer *r = Game::renderer);
	WalkOnObject(std::string id, int red, int green, int blue, SDL_Renderer *r = Game::renderer);
	explicit WalkOnObject(const DisplayObject& other);
	~WalkOnObject() override;

	void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
	void draw(AffineTransform& at) override;

	bool onCollision(DisplayObject* other) override;

private:

};