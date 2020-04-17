#pragma once

#include "DisplayObject.h"
#include "Game.h"

class Sprite : public DisplayObject {

public:
	Sprite(std::string id, SDL_Renderer *r = Game::renderer);
	Sprite(std::string id, std::string filepath, SDL_Renderer *r = Game::renderer);
	Sprite(std::string id, int red, int green, int blue, SDL_Renderer *r = Game::renderer);
	Sprite(const DisplayObject& other);
	virtual ~Sprite();

	void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
	void draw(AffineTransform& at) override;

private:

};
