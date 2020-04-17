#pragma once

#include "EnvironmentObject.h"
#include "Game.h"

class HitObject : public EnvironmentObject {

public:
	HitObject(std::string id, SDL_Renderer *r = Game::renderer);
	HitObject(std::string id, std::string filepath, SDL_Renderer *r = Game::renderer);
	HitObject(std::string id, int red, int green, int blue, SDL_Renderer *r = Game::renderer);
	HitObject(const DisplayObject& other);
	virtual ~HitObject();

	void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons);
	void draw(AffineTransform& at) override;

private:

};