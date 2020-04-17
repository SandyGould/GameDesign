#pragma once

#include "DisplayObject.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include "Camera.h"



#include "json.hpp"

#include <string>
#include <vector>
#include <fstream>

using json = nlohmann::json;

class Scene : public DisplayObject {

public:
	Scene();
	explicit Scene(std::string id);
	// ~Scene() override;

	/* Load scene from a file */
	void loadScene(std::string sceneFilePath);
	void saveScene(std::string sceneName);
	void addToJSON(nlohmann::json &Layer, DisplayObject* dObject);

	void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
	void draw(AffineTransform& at) override;
	void setCameraRef(Camera* camera);

	DisplayObject* generateDO(json j);
	AnimatedSprite* generateAS(json j);
	Sprite* generateSprite(json j);

	// for scene transitions
	bool keepScene = false;
	
private:
	DisplayObject* root;

};
