#pragma once

#include "../AnimatedSprite.h"
#include "../CollisionSystem.h"
#include "Shield.h"

enum class SlideDirection {
    Left,
    Right,
    Up,
    Down,
    None,
};

class Player : public AnimatedSprite {
public:
	Player();

	void changeHealth(int amount);
	void changeStamina(int amount);
	void toggleShieldVisible(bool vis);

	void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;

    bool onCollision(std::shared_ptr<DisplayObject> other, CollisionDirection direction1, CollisionDirection direction2) override;

	std::shared_ptr<Shield> shield;
	double speed = 4.0;
	int health = 100;
	int stamina = 1000;
	bool alive = true;
    SlideDirection slideDirection = SlideDirection::None;
	int numOpponents = 0;

    double deltaX = 0.0;
    double deltaY = 0.0;
    double storedDeltaX = 0.0;
    double storedDeltaY = 0.0;

    bool interacting = false;

private:
	void cannonBallHit(std::shared_ptr<DisplayObject> other);
	std::array<std::unordered_set<SDL_Scancode>, 8> history;
    std::unordered_set<SDL_Scancode> prevKeys;

	void updateHistory(std::unordered_set<SDL_Scancode> pressedKeys);
	bool checkDoubleTaps(SDL_Scancode key);

    int slideFrames = 0;
};
