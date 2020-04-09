#ifndef MAGEATTACK_H
#define MAGEATTACK_H

#include "../Sprite.h"
#include "../events/EventDispatcher.h"

class MageAttack : public Sprite {

public:

    SDL_Point targetPos = {0,0};
    int distX = 0;
    int distY = 0;

	MageAttack();

	void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
	void draw(AffineTransform& at) override;

private:

};

#endif