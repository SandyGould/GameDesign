#include "Scene.h"
#include "AnimatedSprite.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <json.hpp>
using json = nlohmann::json;

Scene::Scene(){}

	/* Load scene from a file */
void Scene::loadScene(string sceneFilePath){
    std::ifstream i(sceneFilePath);
    json j;
    i >> j;
    for(int z = 0; z < j["DOC"].size(); z++){
        std::cout << j["DOC"][z] << endl;
        DisplayObjectContainer* temp_doc = new DisplayObjectContainer(j["DOC"][z]["name"], j["DOC"][z]["filepath"]);
        this->addChild(temp_doc);
    }
    for(int z = 0; z < j["DO"].size(); z++){
        std::cout << j["DO"][z] << endl;
        DisplayObject* temp_do = new DisplayObject(j["DO"][z]["name"], j["DO"][z]["filepath"]);
        this->addChild(temp_do);
    }
    for(int z = 0; z < j["ASprite"].size(); z++){
        std::cout << j["ASprite"][z] << endl;
        AnimatedSprite* temp_asprite = new AnimatedSprite(j["ASprite"][z]["name"]);
        this->addChild(temp_asprite);
    }
    for(int z = 0; z < j["Sprite"].size(); z++){
        std::cout << j["Sprite"][z] << endl;
        Sprite* temp_sprite = new Sprite(j["Sprite"][z]["name"], j["Sprite"][z]["filepath"]);
        this->addChild(temp_sprite);
    }
}

void Scene::update(set<SDL_Scancode> pressedKeys){
    DisplayObjectContainer::update(pressedKeys);
}
void Scene::draw(AffineTransform &at){
    DisplayObjectContainer::draw(at);
}