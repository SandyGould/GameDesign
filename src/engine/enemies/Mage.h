#ifndef MAGE_H
#define MAGE_H

#include "../Sprite.h"
#include "MageAttack.h"

class Mage : public Sprite {

public:

	Mage();
	int ready = 300;

	void changeHealth(int amount);
	MageAttack* attack(Sprite* target);

	void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
	void draw(AffineTransform& at) override;

private:
	double distance(SDL_Point& p1, SDL_Point& p2);
	int health = 100;
};

#endif
