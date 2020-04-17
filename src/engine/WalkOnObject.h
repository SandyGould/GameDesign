#pragma once

#include "events/Event.h"

#include "EnvironmentObject.h"
#include "Game.h"

class WalkOnObject : public EnvironmentObject {

public:
	WalkOnObject(std::string id, SDL_Renderer *r = Game::renderer);
	WalkOnObject(std::string id, std::string filepath, SDL_Renderer *r = Game::renderer);
	WalkOnObject(std::string id, int red, int green, int blue, SDL_Renderer *r = Game::renderer);
	WalkOnObject(const DisplayObject& other);
	virtual ~WalkOnObject();

	void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons);
	void draw(AffineTransform& at) override;

	bool onCollision(DisplayObject* other) override;

private:

};