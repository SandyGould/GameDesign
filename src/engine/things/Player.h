#ifndef PLAYER_H
#define PLAYER_H

#include "../Sprite.h"
#include "../AnimatedSprite.h"
#include "../events/EventDispatcher.h"

class Player : public AnimatedSprite, public EventDispatcher {

public:
	
	Player();

	void update(std::set<SDL_Scancode> pressedKeys) override;
	void draw(AffineTransform& at) override;

private:
	
};

#endif