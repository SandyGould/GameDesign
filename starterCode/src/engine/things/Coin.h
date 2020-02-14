#ifndef COIN_H
#define COIN_H

#include "../Sprite.h"
#include "../events/EventListener.h"

class Coin : public Sprite, public EventListener {

public:
	
	Coin();

	virtual void update(std::set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform& at);

    void handleEvent(Event* e);

private:
	
};

#endif