#ifndef MAGE_H
#define MAGE_H

#include "../CollisionSystem.h"
#include "../projectiles/MageAttack.h"
#include "BaseEnemy.h"

class Mage : public BaseEnemy {

public:

	explicit Mage(std::shared_ptr<Player> player);
	Mage(std::string id, std::shared_ptr<Player> player, std::string filepath, std::string xml, std::string animName);
	int ready = 300;

	void changeHealth(int amount);
	std::shared_ptr<MageAttack> mageAttack;
	std::shared_ptr<MageAttack> attack(std::shared_ptr<Sprite> target);

	void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
    bool onCollision(std::shared_ptr<DisplayObject> other, CollisionDirection direction1, CollisionDirection direction2) override;
};

#endif
