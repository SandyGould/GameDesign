#ifndef SHIELD_H
#define SHIELD_H

#include "../Sprite.h"
#include "../events/EventDispatcher.h"

class Shield : public Sprite {

public:

	Shield();

	void switchType();

	void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
	void draw(AffineTransform& at) override;

	bool onCollision(DisplayObject* other) override;
	bool bashing = false;
	int bashFrames = 0;
private:

	bool magic = false;

};

#endif
