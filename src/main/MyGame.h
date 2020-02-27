#ifndef MYGAME_H
#define MYGAME_H

#include "../engine/Game.h"
#include "../engine/Sprite.h"
#include "../engine/AnimatedSprite.h"
#include "../engine/Scene.h"
#include "../engine/Camera.h"
#include "../engine/things/Coin.h"
#include "../engine/things/Crosshair.h"
#include "../engine/things/Player.h"
#include "../engine/QuestManager.h"
#include "../engine/events/PickedUpEvent.h"
#include "../engine/Scene.h"
#include <vector>

class MyGame : public Game {

public:
	MyGame();
	MyGame(string sceneToLoad);
	virtual ~MyGame();

	void update(std::set<SDL_Scancode> pressedKeys) override;
	void draw(AffineTransform& at) override;

private:
	
	Camera* camera;
	bool inZone = false;
	bool hasChild = false;
	
	//DisplayObjectContainer all_objects;

	Crosshair* crosshair;
	Scene* curScene;

	DisplayObjectContainer* allSprites;

	QuestManager* questManager;

	// DisplayObject* character;
	Scene* scene;
	Scene* scene2;
};

#endif