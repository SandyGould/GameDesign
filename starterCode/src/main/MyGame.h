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
	
	AnimatedSprite* sun;
	Sprite* planet1;
	Sprite* planet2;
	Sprite* moon1_1;

	DisplayObjectContainer* p1container;
	DisplayObjectContainer* p2container;
	DisplayObjectContainer* allSprites;

	// DisplayObject* character;
};

#endif