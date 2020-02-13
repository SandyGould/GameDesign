#include "Scene.h"
#include <string>
#include <vector>
#include <fstream>

Scene::Scene(){}

	/* Load scene from a file */
void Scene::loadScene(string sceneFilePath){
}

void Scene::update(set<SDL_Scancode> pressedKeys){
    DisplayObjectContainer::update(pressedKeys);
}
void Scene::draw(AffineTransform &at){
    DisplayObjectContainer::draw(at);
}