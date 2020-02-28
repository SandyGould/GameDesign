#include "Scene.h"
#include "AnimatedSprite.h"
#include "DisplayObjectContainer.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "json.hpp"
using json = nlohmann::json;
// #include "../dist/json/json.h"



Scene::Scene() : DisplayObjectContainer(){
    this->type = "Scene";
}
Scene::Scene(string id) : DisplayObjectContainer(){
    this->type = "Scene";
    this->id = id;
}
// Scene::~Scene(){
//     delete this;
// }

	/* Load scene from a file */
void Scene::loadScene(string sceneFilePath){
    std::ifstream i(sceneFilePath);
    json j;
    i >> j;
    for(int z = 0; z < j["DOC"].size(); z++){
        // std::cout << j["DOC"][z] << endl;
        DisplayObjectContainer* temp_doc = new DisplayObjectContainer(j["DOC"][z]["name"], j["DOC"][z]["filepath"]);
        /* Assuming we have these fields in the json for each object */
        temp_doc->position.x = j["DOC"][z]["x_pos"];
        temp_doc->position.y = j["DOC"][z]["y_pos"];
        temp_doc->rotation = j["DOC"][z]["rotation"];
        temp_doc->scaleX = j["DOC"][z]["scaleX"];
        temp_doc->scaleY = j["DOC"][z]["scaleY"];
        this->addChild(temp_doc);
    }
    for(int z = 0; z < j["DO"].size(); z++){
        // std::cout << j["DO"][z] << endl;
        DisplayObject* temp_do = new DisplayObject(j["DO"][z]["name"], j["DO"][z]["filepath"]);
        temp_do->position.x = j["DO"][z]["x_pos"];
        temp_do->position.y = j["DO"][z]["y_pos"];
        temp_do->rotation = j["DO"][z]["rotation"];
        temp_do->scaleX = j["DO"][z]["scaleX"];
        temp_do->scaleY = j["DO"][z]["scaleY"];
        this->addChild(temp_do);
    }
    for(int z = 0; z < j["ASprite"].size(); z++){
        // std::cout << j["ASprite"][z] << endl;
        AnimatedSprite* temp_asprite = new AnimatedSprite(j["ASprite"][z]["name"]);
        temp_asprite->addAnimation(j["ASprite"][z]["basepath"], j["ASprite"][z]["animName"], j["ASprite"][z]["numFrames"], j["ASprite"][z]["frameRate"], j["ASprite"][z]["loop"]);
        temp_asprite->position.x = j["ASprite"][z]["x_pos"];
        temp_asprite->position.y = j["ASprite"][z]["y_pos"];
        temp_asprite->rotation = j["ASprite"][z]["rotation"];
        temp_asprite->scaleX = j["ASprite"][z]["scaleX"];
        temp_asprite->scaleY = j["ASprite"][z]["scaleY"];
        this->addChild(temp_asprite);
        temp_asprite->play(j["ASprite"][z]["animName"]);
    }
    for(int z = 0; z < j["Sprite"].size(); z++){
        // std::cout << j["Sprite"][z] << endl;
        Sprite* temp_sprite = new Sprite(j["Sprite"][z]["name"], j["Sprite"][z]["filepath"]);
        this->addChild(temp_sprite);
    }
    // Json::Value scene_info;
	// //Json::Reader reader;

    // root = new DisplayObjectContainer();

    // ifstream scene_file(sceneFilePath, ifstream::binary);
    // scene_file >> scene_info;
    // for(int x = 0; x < this->children.size();x++){
    //     std::cout << children[x]->id << endl;
    // }
    
}

void Scene::saveScene(string sceneName){
    std::ofstream o("./resources/scene/" + sceneName);
    json DOA = json::array();
    json DOCA = json::array();
    json ASA = json::array();
    json SA = json::array();
    addToJSON(DOA, DOCA, ASA, SA, this);
    json j = { {"DO", DOA}, {"DOC", DOCA}, {"ASprite", ASA}, {"Sprite", SA} };
    o << j;
}

void Scene::addToJSON(json &DOA, json &DOCA, json &ASA, json &SA, DisplayObject* dObject){
    //save stuff
    if (dObject->type == "DisplayObject"){
        //j["DO"].push_back({ {"name", dObject->id}, {"filepath", dObject->imgPath}, {"x_pos", dObject->position.x}, {"y_pos", dObject->position.y}, {"rotation", dObject->rotation}, {"scaleX", dObject->scaleX}, {"scaleY", dObject->scaleY}, {"parentId", dObject->parentId} });
    } else if (dObject->type == "DisplayObjectContainer"){
        cout << "trying" << endl;
        //json temp = { {"name", dObject->id}, {"filepath", dObject->imgPath}, {"x_pos", dObject->position.x}, {"y_pos", dObject->position.y}, {"rotation", dObject->rotation}, {"scaleX", dObject->scaleX}, {"scaleY", dObject->scaleY}, {"parentId", dObject->parentId} };
        cout << "really hard" << endl;
        DOCA.push_back({ {"name", dObject->id}, {"filepath", dObject->imgPath}, {"x_pos", dObject->position.x}, {"y_pos", dObject->position.y}, {"rotation", dObject->rotation}, {"scaleX", dObject->scaleX}, {"scaleY", dObject->scaleY}, {"parentId", dObject->parentId} });
    } else if (dObject->type == "Sprite"){
        //j["Sprite"].push_back({ {"name", dObject->id}, {"filepath", dObject->imgPath}, {"x_pos", dObject->position.x}, {"y_pos", dObject->position.y}, {"rotation", dObject->rotation}, {"scaleX", dObject->scaleX}, {"scaleY", dObject->scaleY}, {"parentId", dObject->parentId} });
    } else if (dObject->type == "AnimatedSprite"){
        //j["Sprite"].push_back({ {"name", dObject->id}, {"filepath", dObject->imgPath}, {"x_pos", dObject->position.x}, {"y_pos", dObject->position.y}, {"rotation", dObject->rotation}, {"scaleX", dObject->scaleX}, {"scaleY", dObject->scaleY}, {"parentId", dObject->parentId} });
    }

    if(dObject->type != "DisplayObject"){
        DisplayObjectContainer* temp = (DisplayObjectContainer*) dObject;
        for (auto child : temp->children){
            addToJSON(DOA, DOCA, ASA, SA, child);
        }
    }
}

void Scene::update(unordered_set<SDL_Scancode> pressedKeys){
    DisplayObjectContainer::update(pressedKeys);
}
void Scene::draw(AffineTransform &at){
    DisplayObjectContainer::draw(at);
}
