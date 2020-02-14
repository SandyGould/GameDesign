#ifndef PLAYER_H
#define PLAYER_H

#include "../Sprite.h"
#include "../events/EventDispatcher.h"

class Player : public Sprite, public EventDispatcher {

public:
	
	Player();

	virtual void update(std::set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform& at);

private:
	
};

#endif