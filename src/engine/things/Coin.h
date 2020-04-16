#ifndef COIN_H
#define COIN_H

#include "../Sprite.h"
#include "../events/EventListener.h"

class Coin : public Sprite, EventListener {

public:

	Coin();

	virtual void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons);
	virtual void draw(AffineTransform& at);

    void handleEvent(Event* e) override;

private:

};

#endif
