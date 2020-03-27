#ifndef SHIELD_H
#define SHIELD_H

#include "../Sprite.h"
#include "../events/EventDispatcher.h"

class Shield : public Sprite, public EventDispatcher {

public:

	Shield();

	void update(std::set<SDL_Scancode> pressedKeys) override;
	void draw(AffineTransform& at) override;

private:

};

#endif
