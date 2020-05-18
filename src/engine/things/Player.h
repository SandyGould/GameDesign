#pragma once

#include "../AnimatedSprite.h"
#include "../CollisionSystem.h"
#include "../tweens/TweenJuggler.h"
#include "Shield.h"

class Player : public AnimatedSprite {
public:
	Player();

	void changeHealth(int amount);
	void changeStamina(int amount);
	void toggleShieldVisible(bool vis);

	void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;

    bool onCollision(std::shared_ptr<DisplayObject> other, CollisionDirection direction1, CollisionDirection direction2) override;

	std::shared_ptr<Shield> shield;
	double speed = 4;
	bool speedChange = false;
	int health = 100;
	int stamina = 1000;
	bool alive = true;
	bool slidin = false;
	int numOpponents = 0;

private:
	int shieldSwitchCooldown;
	int shieldBashCooldown;
	
	void cannonBallHit(std::shared_ptr<DisplayObject> other);
	std::unordered_set<SDL_Scancode>* history;
    std::unordered_set<SDL_Scancode> prevKeys;

	void updateHistory(std::unordered_set<SDL_Scancode> pressedKeys);
	bool checkDoubleTaps(SDL_Scancode key);
};
