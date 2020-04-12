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

	void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
	void draw(AffineTransform& at) override;
	void draw(AffineTransform& at, SDL_Renderer* r, SDL_Rect* src = NULL) override;

private:

};
