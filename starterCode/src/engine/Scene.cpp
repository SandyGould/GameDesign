#include "Scene.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "../dist/json/json.h"



Scene::Scene(){}

	/* Load scene from a file */
void Scene::loadScene(string sceneFilePath){
    Json::Value scene_info;
	//Json::Reader reader;

    root = new DisplayObjectContainer();

    ifstream scene_file(sceneFilePath, ifstream::binary);
    scene_file >> scene_info;
    
}

void Scene::update(set<SDL_Scancode> pressedKeys){
    DisplayObjectContainer::update(pressedKeys);
}
void Scene::draw(AffineTransform &at){
    DisplayObjectContainer::draw(at);
}