#pragma once

#include "EnvironmentObject.h"
#include "Game.h"

class HitObject : public EnvironmentObject {

public:
	explicit HitObject(std::string id, SDL_Renderer *r = Game::renderer);
	HitObject(std::string id, std::string filepath, SDL_Renderer *r = Game::renderer);
	HitObject(std::string id, int red, int green, int blue, SDL_Renderer *r = Game::renderer);
	explicit HitObject(const DisplayObject& other);
	~HitObject() override;

	void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
	void draw(AffineTransform& at) override;

private:

};