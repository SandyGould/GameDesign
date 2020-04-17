#pragma once

#include "Sprite.h"
#include "Game.h"

class EnvironmentObject : public Sprite {

public:
	EnvironmentObject(std::string id, SDL_Renderer *r = Game::renderer);
	EnvironmentObject(std::string id, std::string filepath, SDL_Renderer *r = Game::renderer);
	EnvironmentObject(std::string id, int red, int green, int blue, SDL_Renderer *r = Game::renderer);
	EnvironmentObject(const DisplayObject& other);
	virtual ~EnvironmentObject();

	void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons);
	void draw(AffineTransform& at) override;

private:

};