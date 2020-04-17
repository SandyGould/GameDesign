#pragma once

#include "../engine/Camera.h"
#include "../engine/CollisionSystem.h"
#include "../engine/Game.h"
#include "../engine/Scene.h"
#include "../engine/TextObject.h"
#include "../engine/events/EventListener.h"
#include "../engine/events/MouseDownEvent.h"
#include "../engine/events/MouseMotionEvent.h"
#include "../engine/events/MouseUpEvent.h"
#include "../engine/events/MouseWheelEvent.h"
#include "../engine/events/TextEditEvent.h"
#include "../engine/events/TextInputEvent.h"
#include "../engine/events/WindowEnterEvent.h"
#include "../engine/events/WindowExitEvent.h"

#include <algorithm>
#include <filesystem>
#include <iterator>
#include <vector>

using namespace std;

class Editor : public Game, public EventListener {
public:
	Editor();
	Editor(const string& sceneToLoad);

	void setupfiles(const string& path);

	void update(unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
	void draw(AffineTransform& at) override;
	void initSDL();
	void draw_post() override;
	void clearRenderers() override;
	void presentRenderers() override;

	void cut(const unordered_set<DisplayObject*>& objects);
	void copy(const unordered_set<DisplayObject*>& objects, bool keepHierarchy = true);
	void paste(MouseDownEvent* event = NULL);

	void handleEvent(Event* e) override;

	bool onMouseDown(DisplayObject* object, MouseDownEvent* event);
	bool onMouseUp(DisplayObject* object, MouseUpEvent* event);

	SDL_Window* assets_window;
	SDL_Renderer* assets_renderer;

	SDL_Window* edit_window;
	SDL_Renderer* edit_renderer;

private:
	Camera* camera;
	Scene* curScene;

	vector<Sprite*> sprites;
	vector<DisplayObject*> dos;
	vector<AnimatedSprite*> aSprites;

	DisplayObject* assets;
	DisplayObject* edit;

	bool mainWindowActive = true;
	bool assetsWindowActive = false;
	bool editWindowActive = false;
	DisplayObject* selectedAsset = NULL;

	DisplayObject* editSelected = NULL;
	TextObject* attributeSelected = NULL;
	unordered_set<DisplayObject*> editable;
	bool setParentMode = false;
	void updateAttribute();
	int layer = 0;

	SDL_Point heldPosition = {0, 0};
	SDL_Point heldPivot = {0, 0};
	double heldScaleX = 1.0;
	double heldScaleY = 1.0;
	double heldRotation = 0.0;

	unordered_set<DisplayObject*> selected;
	unordered_set<DisplayObject*> copied;

	unordered_set<SDL_Scancode> prevKeys;

    // Oh boy
    unordered_map<DisplayObject*, double> displacementX;
    unordered_map<DisplayObject*, double> displacementY;

    static constexpr int GRID_SIZE = 80;
    CollisionSystem* collisionSystem;
};