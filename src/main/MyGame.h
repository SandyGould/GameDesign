#ifndef MYGAME_H
#define MYGAME_H

#include "../engine/Game.h"
#include "../engine/Sprite.h"
#include "../engine/AnimatedSprite.h"
#include "../engine/Scene.h"
#include "../engine/things/Coin.h"
#include "../engine/things/Player.h"
#include "../engine/QuestManager.h"
#include "../engine/events/PickedUpEvent.h"

class MyGame : public Game {

public:
	MyGame();
	virtual ~MyGame();

	void update(std::set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons);
	void draw(AffineTransform& at) override;

private:
	const int DEAD_ZONE = 8000;

	Player* player;
	Coin* coin;

	DisplayObjectContainer* allSprites;

	QuestManager* questManager;

	// DisplayObject* character;
	Scene* scene;
	Scene* scene2;
};

#endif