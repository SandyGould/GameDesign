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

	void update(unordered_set<SDL_Scancode> pressedKeys) override;
	void draw(AffineTransform &at) override;


private:
	DisplayObjectContainer* root;

};

#endif
