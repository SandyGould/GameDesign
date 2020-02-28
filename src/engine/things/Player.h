#ifndef PLAYER_H
#define PLAYER_H

#include "../Sprite.h"
#include "../events/EventDispatcher.h"

class Player : public Sprite, public EventDispatcher {

public:

	Player();

	void update(std::unordered_set<SDL_Scancode> pressedKeys) override;
	void draw(AffineTransform& at) override;

private:

};

#endif
