#ifndef SPRITE_H
#define SPRITE_H

#include "DisplayObjectContainer.h"

class Sprite : public DisplayObjectContainer {

public:
	Sprite();
	Sprite(std::string id, std::string filepath);
	Sprite(std::string id, int red, int green, int blue);

	virtual void update(std::set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform& at);
private:
	
};

#endif