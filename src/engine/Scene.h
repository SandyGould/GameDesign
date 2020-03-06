#ifndef SCENE_H
#define SCENE_H

#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "AnimatedSprite.h"
#include "Sprite.h"

#include "json.hpp"

#include <string>
#include <vector>
#include <fstream>

using json = nlohmann::json;

class Scene : public DisplayObjectContainer{

public:
	Scene();
	Scene(std::string id);
	// virtual ~Scene();

	/* Load scene from a file */
	void loadScene(std::string sceneFilePath);
	void saveScene(std::string sceneName);
	void addToJSON(nlohmann::json &DOA, nlohmann::json &DOCA, nlohmann::json &ASA, nlohmann::json &SA, DisplayObject* dObject);


	void update(std::unordered_set<SDL_Scancode> pressedKeys) override;
	void draw(AffineTransform &at) override;

	DisplayObjectContainer* generateDOC(json j);
	AnimatedSprite* generateAS(json j);
	Sprite* generateSprite(json j);
	
private:
	DisplayObjectContainer* root;

};

#endif
