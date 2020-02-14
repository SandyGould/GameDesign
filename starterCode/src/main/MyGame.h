#ifndef MYGAME_H
#define MYGAME_H

#include "../engine/Game.h"
#include "../engine/Sprite.h"
#include "../engine/AnimatedSprite.h"

using namespace std;

class MyGame : public Game {

public:
	MyGame();
	virtual ~MyGame();

	void update(set<SDL_Scancode> pressedKeys) override;
	void draw(AffineTransform& at) override;

private:
	
	Sprite* player;
	Sprite* coin;

	DisplayObjectContainer* allSprites;

	// DisplayObject* character;
};

#endif