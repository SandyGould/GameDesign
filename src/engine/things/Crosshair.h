#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include "../Sprite.h"
#include "../events/EventDispatcher.h"

class Crosshair : public Sprite, public EventDispatcher {

public:

	Crosshair();

	void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
	void draw(AffineTransform& at) override;

private:

};

#endif
