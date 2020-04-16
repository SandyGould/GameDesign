#pragma once

#include "DisplayObject.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include "Camera.h"
#include "../events/Event.h"
#include "../events/EventListener.h"


#include "json.hpp"

#include <string>
#include <vector>
#include <fstream>

using json = nlohmann::json;

class Scene : public DisplayObject, public EventListener {

public:
	Scene();
	Scene(std::string id);
	// virtual ~Scene();

	/* Load scene from a file */
	void loadScene(std::string sceneFilePath);
	void saveScene(std::string sceneName);
	void addToJSON(nlohmann::json &Layer, DisplayObject* dObject);

	virtual void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons);
	// virtual void draw(AffineTransform &at);
	void draw(AffineTransform& at) override;
	void draw(AffineTransform& at, SDL_Renderer* r, SDL_Rect* src = NULL) override;
	void setCameraRef(Camera* camera);

	DisplayObject* generateDO(json j);
	AnimatedSprite* generateAS(json j);
	Sprite* generateSprite(json j);

	// for scene transitions
	void handleEvent(Event* e);
	bool keepScene = false;
	
private:
	DisplayObject* root;

};
