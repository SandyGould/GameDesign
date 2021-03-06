#ifndef COIN_H
#define COIN_H

#include "../Sprite.h"
#include "../events/EventListener.h"

class Coin : public Sprite {

public:

	Coin();

	virtual void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
	virtual void draw(AffineTransform& at) override;

    void handleEvent(Event* e) override;

private:

};

#endif