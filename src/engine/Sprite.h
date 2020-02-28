#ifndef SPRITE_H
#define SPRITE_H

#include "DisplayObjectContainer.h"

class Sprite : public DisplayObjectContainer {

public:
	Sprite();
	Sprite(std::string id, std::string filepath);
	Sprite(std::string id, int red, int green, int blue);

	void update(std::unordered_set<SDL_Scancode> pressedKeys) override;
	void draw(AffineTransform& at) override;
private:

};

#endif
