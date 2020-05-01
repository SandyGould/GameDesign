#pragma once

#include "../engine/Camera.h"
#include "../engine/CollisionSystem.h"
#include "../engine/Game.h"
#include "../engine/Scene.h"
#include "../engine/Layer.h"
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

class Editor : public Game {
public:
	Editor();
	Editor(const string& sceneToLoad);

	void setupfiles(const string& path);

	void update(const unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const unordered_set<Uint8>& pressedButtons) override;
	void draw(AffineTransform& at) override;
	void initSDL();
	void draw_post() override;
	void clearRenderers() override;
	void presentRenderers() override;

	void cut(const unordered_set<shared_ptr<DisplayObject>>& objects);
	void copy(const unordered_set<shared_ptr<DisplayObject>>& objects, bool keepHierarchy = true);
	void paste(MouseDownEvent* event = NULL);

	void handleEvent(Event* e) override;

	bool onMouseDown(shared_ptr<DisplayObject> object, MouseDownEvent* event);
	bool onMouseUp(shared_ptr<DisplayObject> object, MouseUpEvent* event);

	SDL_Window* assets_window;
	SDL_Renderer* assets_renderer;

	SDL_Window* edit_window;
	SDL_Renderer* edit_renderer;

private:
	std::shared_ptr<Camera> camera;
	std::shared_ptr<Scene> curScene;

	vector<std::shared_ptr<Sprite>> sprites;
	vector<std::shared_ptr<DisplayObject>> dos;
	vector<std::shared_ptr<AnimatedSprite>> aSprites;

	shared_ptr<DisplayObject> assets;
	shared_ptr<DisplayObject> edit;

	bool mainWindowActive = true;
	bool assetsWindowActive = false;
	bool editWindowActive = false;
	shared_ptr<DisplayObject> selectedAsset = nullptr;

	bool freeMove = true;
	bool incrSnap = false;
	bool gridSnap = false;

	shared_ptr<TextObject> editSelected = nullptr;
	shared_ptr<TextObject> attributeSelected = nullptr;
	unordered_set<shared_ptr<DisplayObject>> editable;
	bool setParentMode = false;
	void updateAttribute();
	int layer = 0;

	SDL_Point heldPosition = {0, 0};
	SDL_Point heldPivot = {0, 0};
	double heldScaleX = 1.0;
	double heldScaleY = 1.0;
	double heldRotation = 0.0;

	unordered_set<shared_ptr<DisplayObject>> selected;
	unordered_set<shared_ptr<DisplayObject>> copied;

	unordered_set<SDL_Scancode> prevKeys;

	unordered_set<string> entityTypes;

    // Oh boy
    unordered_map<shared_ptr<DisplayObject>, double> displacementX;
    unordered_map<shared_ptr<DisplayObject>, double> displacementY;

    static constexpr int GRID_SIZE = 80;
};
