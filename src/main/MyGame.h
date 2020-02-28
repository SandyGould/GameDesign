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
#include <iterator>
#include <algorithm>
#include <stdio.h>
#include <dirent.h>
//#include <filesystem>

class MyGame : public Game {

public:
	MyGame();
	MyGame(string sceneToLoad);
	virtual ~MyGame();

	void update(std::unordered_set<SDL_Scancode> pressedKeys) override;
	void draw(AffineTransform& at) override;
	void copyDisplayObjectContainer(DisplayObjectContainer *newobj, DisplayObjectContainer *oldobj);
	void copyDisplayObject(DisplayObject* newobj, DisplayObject *oldobj);
	void setupfiles(string path);
private:

	Camera* camera;
	bool inZone = false;
	bool hasChild = false;
	bool grabbedObj = false;
	int obj_ind = 0;
	DisplayObjectContainer all_objects;
	vector<string> all_sprites;
	Crosshair* crosshair;
	Scene* curScene;

	AffineTransform atTest;

	//DisplayObjectContainer* allSprites;

	QuestManager* questManager;

	// DisplayObject* character;
	Scene* scene;
	Scene* scene2;

	std::unordered_set<SDL_Scancode> prevKeys;
};

#endif
