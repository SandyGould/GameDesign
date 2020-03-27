#ifndef MYGAME_H
#define MYGAME_H

#include "../engine/Game.h"
#include "../engine/Sprite.h"
#include "../engine/AnimatedSprite.h"
#include "../engine/Scene.h"
#include "../engine/things/Coin.h"
#include "../engine/things/Player.h"
#include "../engine/things/Shield.h"
#include "../engine/QuestManager.h"
#include "../engine/events/PickedUpEvent.h"

class MyGame : public Game {

public:
	MyGame();
	virtual ~MyGame();

	void update(std::set<SDL_Scancode> pressedKeys) override;
	void draw(AffineTransform& at) override;

private:

	Player* player;
	Coin* coin;
	Shield* shield;

	DisplayObjectContainer* allSprites;

	QuestManager* questManager;

	// DisplayObject* character;
	Scene* scene;
	Scene* scene2;
};

#endif
