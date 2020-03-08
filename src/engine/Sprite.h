#pragma once

#include "DisplayObject.h"

class Sprite : public DisplayObject {

public:
	Sprite(std::string id);
	Sprite(std::string id, std::string filepath);
	Sprite(std::string id, int red, int green, int blue);

	void update(std::unordered_set<SDL_Scancode> pressedKeys) override;
	void draw(AffineTransform& at) override;
	void draw(AffineTransform& at, SDL_Renderer* r, SDL_Rect* src = NULL) override;
private:

};
