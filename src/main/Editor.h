#pragma once

#include "../engine/Game.h"
#include "../engine/Camera.h"
#include "../engine/Scene.h"
#include "../engine/events/EventListener.h"
#include "../engine/things/Crosshair.h"

#include <vector>
#include <iterator>
#include <algorithm>
#include <dirent.h>

using namespace std;

class Editor : public Game, public EventListener {
public:
	Editor();
	Editor(const string& sceneToLoad);

	void setupfiles(const string& path);

	void update(std::unordered_set<SDL_Scancode> pressedKeys) override;
	void draw(AffineTransform& at) override;

	void handleEvent(Event* e) override;

	bool selectObject(DisplayObject* object, int x, int y);
	bool dragObject(DisplayObject* object, int x, int y, int xrel, int yrel);

private:
	Camera* camera;
	bool inZone = false;
	bool hasChild = false;
	bool grabbedObj = false;
	int obj_ind = 0;
	vector<string> all_sprites;
	Crosshair* crosshair;
	Scene* curScene;

	AffineTransform atTest;

	SDL_Point heldPosition = {0, 0};
	SDL_Point heldPivot = {0, 0};
	double heldScaleX = 1.0;
	double heldScaleY = 1.0;
	double heldRotation = 0.0;

	DisplayObject* selected;

	std::unordered_set<SDL_Scancode> prevKeys;
};
