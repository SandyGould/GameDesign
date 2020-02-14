#include "Scene.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "../dist/json/json.h"



Scene::Scene(){}

	/* Load scene from a file */
void Scene::loadScene(string sceneFilePath){
    root = new DisplayObjectContainer();

    ifstream scene_file(sceneFilePath, ifstream::binary);
    scene_file >> scene_info;
    // all the display objects in the scene are in scene info;
    // now have to parse through, extract info, and add as children
    // to root
    
}

void Scene::update(set<SDL_Scancode> pressedKeys){
    DisplayObjectContainer::update(pressedKeys);
}
void Scene::draw(AffineTransform &at){
    DisplayObjectContainer::draw(at);
}