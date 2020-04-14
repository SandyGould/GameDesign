#ifndef SHIELD_H
#define SHIELD_H

#include "../Sprite.h"
#include "../events/EventDispatcher.h"

class Shield : public Sprite {

public:

	Shield();

	void switchType();

	void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
	void draw(AffineTransform& at) override;

	bool onCollision(DisplayObject* other);
private:

	bool magic = false;

};

#endif
