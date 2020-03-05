#ifndef SCENE_H
#define SCENE_H

#include "DisplayObjectContainer.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include <string>
#include <vector>
#include <fstream>
#include <json.hpp>

using json = nlohmann::json;

class Scene : public DisplayObjectContainer{

public:
	Scene();
	Scene(std::string id);
	// virtual ~Scene();

	/* Load scene from a file */
	void loadScene(std::string sceneFilePath);

	DisplayObjectContainer* generateDOC(json j);
	AnimatedSprite* generateAS(json j);
	Sprite* generateSprite(json j);

	virtual void update(std::set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	
private:
	
};

#endif