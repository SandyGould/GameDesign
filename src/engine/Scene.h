#ifndef SCENE_H
#define SCENE_H

#include "DisplayObjectContainer.h"
#include "Sprite.h"
#include <string>
#include <vector>
#include <fstream>
#include "../dist/json/json.h"




using namespace std;

class Scene : public DisplayObjectContainer{

public:
	Scene();
	Scene(string id);
	// virtual ~Scene();

	/* Load scene from a file */
	void loadScene(string sceneFilePath);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);


private:
	DisplayObjectContainer* root;
	
};

#endif