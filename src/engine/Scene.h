#ifndef SCENE_H
#define SCENE_H

#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "Sprite.h"
#include <string>
#include <vector>
#include <fstream>
//#include "../dist/json/json.h"
#include "json.hpp"




using namespace std;

class Scene : public DisplayObjectContainer{

public:
	Scene();
	Scene(string id);
	// virtual ~Scene();

	/* Load scene from a file */
	void loadScene(string sceneFilePath);
	void saveScene(string sceneName);
	void addToJSON(nlohmann::json &DOA, nlohmann::json &DOCA, nlohmann::json &ASA, nlohmann::json &SA, DisplayObject* dObject);


	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);


private:
	DisplayObjectContainer* root;
	
};

#endif