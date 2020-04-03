#pragma once

#include "DisplayObject.h"
#include "AnimatedSprite.h"
#include "Sprite.h"

#include "json.hpp"

#include <string>
#include <vector>
#include <fstream>

using json = nlohmann::json;

class Scene : public DisplayObject {

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

	DisplayObject* generateDO(json j);
	AnimatedSprite* generateAS(json j);
	Sprite* generateSprite(json j);
	
private:
	DisplayObject* root;

};
