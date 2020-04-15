#ifndef PLAYER_H
#define PLAYER_H

#include "../Sprite.h"
#include "Shield.h"
#include "../AnimatedSprite.h"
#include "../tweens/TweenJuggler.h"
#include "../tweens/Tween.h"

class Player : public AnimatedSprite {

public:

	Player();

	void changeHealth(int amount);
	void changeStamina(int amount);

	void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
	void draw(AffineTransform& at) override;

	//bool onCollision(DisplayObject* other);

private:
	int health = 100;
	int stamina = 1000;
	int shieldSwitchCooldown;
	int shieldBashCooldown;
	bool hit;
	void cannonBallHit(DisplayObject* other);
	std::unordered_set<SDL_Scancode>* history;

	void updateHistory(std::unordered_set<SDL_Scancode> pressedKeys);
	bool checkDoubleTaps(SDL_Scancode key);

	Shield* shield;
	Tween* shieldBash;

	TweenJuggler* juggler;

};

#endif