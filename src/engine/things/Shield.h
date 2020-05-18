#pragma once

#include "../Sprite.h"

class Shield : public Sprite {
public:
	Shield();

	void switchType();

	void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;

    bool onCollision(std::shared_ptr<DisplayObject> other, CollisionDirection direction1, CollisionDirection direction2) override;

private:
    bool bashing = false;
    int bashFrames = 0;
	bool magic = false;

    friend class Player;
};
