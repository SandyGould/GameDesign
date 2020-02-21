#ifndef SCENE_H
#define SCENE_H

#include "DisplayObjectContainer.h"
#include "Sprite.h"
#include <string>
#include <vector>
#include <fstream>

class Scene : public DisplayObjectContainer{

public:
	Scene();
	Scene(std::string id);
	// virtual ~Scene();

	/* Load scene from a file */
	void loadScene(std::string sceneFilePath);

	virtual void update(std::set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	
private:
	
};

#endif