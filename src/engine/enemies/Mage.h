#ifndef MAGE_H
#define MAGE_H

#include "BaseEnemy.h"
#include "MageAttack.h"

class Mage : public BaseEnemy {

public:

	Mage(Player* player);

	int ready = 300;

	void changeHealth(int amount);
	MageAttack* mageAttack;
	MageAttack* attack(Sprite* target);

	void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;

};

#endif
