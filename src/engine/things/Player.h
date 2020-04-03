#ifndef PLAYER_H
#define PLAYER_H

#include "../Sprite.h"
#include "../AnimatedSprite.h"

class Player : public AnimatedSprite {

public:

	Player();

	void changeHealth(int amount);
	void changeStamina(int amount);

	void update(std::set<SDL_Scancode> pressedKeys) override;
	void draw(AffineTransform& at) override;

private:
	int health;
	int stamina;
};

#endif
