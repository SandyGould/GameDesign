#ifndef PLAYER_H
#define PLAYER_H

#include "../Sprite.h"
#include "../AnimatedSprite.h"
#include "../events/EventDispatcher.h"

class Player : public AnimatedSprite, public EventDispatcher {

public:

	Player();

	void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
	void draw(AffineTransform& at) override;

private:

};

#endif
