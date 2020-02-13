#include "Scene.h"
#include <string>
#include <vector>
#include <fstream>
// #include <json/value.h>

Scene::Scene(){}

	/* Load scene from a file */
void Scene::loadScene(string sceneFilePath){
    // std::ifstream people_file(sceneFilePath, std::ifstream::binary);
    // people_file >> people;
}

void Scene::update(set<SDL_Scancode> pressedKeys){
    DisplayObjectContainer::update(pressedKeys);
}
void Scene::draw(AffineTransform &at){
    DisplayObjectContainer::draw(at);
}