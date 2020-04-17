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

	void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
	bool onCollision(DisplayObject* other) override;
};

#endif
