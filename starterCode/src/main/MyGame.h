#ifndef MYGAME_H
#define MYGAME_H

#include "../engine/Game.h"
#include "../engine/Sprite.h"
#include "../engine/AnimatedSprite.h"
#include "../engine/things/Coin.h"

class MyGame : public Game {

public:
	MyGame();
	virtual ~MyGame();

	void update(std::set<SDL_Scancode> pressedKeys) override;
	void draw(AffineTransform& at) override;

private:
	
	Sprite* player;
	Coin* coin;

	DisplayObjectContainer* allSprites;

	// DisplayObject* character;
};

#endif