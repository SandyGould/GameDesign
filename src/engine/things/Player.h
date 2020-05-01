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
	void toggleShieldVisible(bool vis);

	void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
	void draw(AffineTransform& at) override;

	bool onCollision(std::shared_ptr<DisplayObject> other) override;
	std::shared_ptr<Shield> shield;
	double speed = 4;
	bool speedChange = false;
	int health = 100;
	int stamina = 1000;
	int numOpponents = 0;

private:
	int shieldSwitchCooldown;
	int shieldBashCooldown;
	bool alive = true;
	void cannonBallHit(std::shared_ptr<DisplayObject> other);
	std::unordered_set<SDL_Scancode>* history;

	void updateHistory(std::unordered_set<SDL_Scancode> pressedKeys);
	bool checkDoubleTaps(SDL_Scancode key);

	std::shared_ptr<Tween> shieldBash;
	std::shared_ptr<Tween> damage;

};

#endif
