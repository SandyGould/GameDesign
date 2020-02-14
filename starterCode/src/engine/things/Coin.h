#ifndef COIN_H
#define COIN_H

#include "Sprite.h"
#include "EventListener.h"

class Coin : public Sprite, public EventListener {

public:
	
	Coin();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform& at);

    void handleEvent(Event* e);

private:
	
};

#endif