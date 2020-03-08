#include "Scene.h"
#include "AnimatedSprite.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "json.hpp"
using json = nlohmann::json;

using namespace std;

Scene::Scene() : Scene("scene") {}

Scene::Scene(std::string id) : DisplayObject(id) {
    this->type = "Scene";
}
// Scene::~Scene(){
//     delete this;
// }

	/* Load scene from a file */
void Scene::loadScene(std::string sceneFilePath){
    std::ifstream i(sceneFilePath);
    json j;
    i >> j;
    for(int z = 0; z < j["Scene"].size(); z++){
        std::string layer_value = "L" + std::to_string(z);
        DisplayObject* temp_layer = new DisplayObject(layer_value);
        json json_layer = j["Scene"][z][layer_value];

        temp_layer->parallaxSpeed = json_layer["speed"];

        for(int y = 0; y < json_layer["objects"].size(); y++){
            // std::cout << "type: " + json_layer["objects"][y]["type"].get<std::string>() << std::endl;
            
            // DisplayObjectContainer* parent = temp_layer;
            // if(json_layer["objects"][y]["parentHierarchy"].size() > 0){
            //     parent = find_parent(json_layer["objects"][y]["parentHierarchy"], temp_layer);
            // } 

            std::string obj_type = json_layer["objects"][y]["type"].get<std::string>();
            if(obj_type.compare("DO") == 0){
                temp_layer->addChild(generateDO(json_layer["objects"][y]));
            }
            else if(obj_type.compare("AnimatedSprite") == 0){
                temp_layer->addChild(generateAS(json_layer["objects"][y]));
            }
            else if(obj_type.compare("Sprite") == 0){
                temp_layer->addChild(generateSprite(json_layer["objects"][y]));
            }
        }
        this->addChild(temp_layer);
    }
}

DisplayObject* Scene::generateDO(json j){
    DisplayObject* temp_do = new DisplayObject(j["name"], j["filepath"]);
    temp_do->position.x = j["x_pos"];
    temp_do->position.y = j["y_pos"];
    temp_do->rotation = j["rotation"];
    temp_do->scaleX = j["scaleX"];
    temp_do->scaleY = j["scaleY"];
    return temp_do;
}

AnimatedSprite* Scene::generateAS(json j){
    AnimatedSprite* temp_asprite = new AnimatedSprite(j["name"]);
    if(j["animations"].size() > 0){
        json ani_json = j["animations"];
        for(int x = 0; x < j["animations"].size(); x++){
            temp_asprite->addAnimation(ani_json[x]["basepath"], ani_json[x]["animName"], ani_json[x]["numFrames"], ani_json[x]["frameRate"], ani_json[x]["loop"]);
        }
        temp_asprite->play(ani_json[0]["animName"]);
    }
    // temp_asprite->addAnimation(j["ASprite"][z]["basepath"], j["ASprite"][z]["animName"], j["ASprite"][z]["numFrames"], j["ASprite"][z]["frameRate"], j["ASprite"][z]["loop"]);
    temp_asprite->position.x = j["x_pos"];
    temp_asprite->position.y = j["y_pos"];
    temp_asprite->rotation = j["rotation"];
    temp_asprite->scaleX = j["scaleX"];
    temp_asprite->scaleY = j["scaleY"];
    return temp_asprite;
}

Sprite* Scene::generateSprite(json j){
    Sprite* temp_sprite = new Sprite(j["name"], j["filepath"]);
    temp_sprite->position.x = j["x_pos"];
    temp_sprite->position.y = j["y_pos"];
    temp_sprite->rotation = j["rotation"];
    temp_sprite->scaleX = j["scaleX"];
    temp_sprite->scaleY = j["scaleY"];
    return temp_sprite;
}

void Scene::saveScene(string sceneName){
    std::ofstream o("./resources/scene/" + sceneName);
    json DOA = json::array();
    json ASA = json::array();
    json SA = json::array();
    addToJSON(DOA, ASA, SA, this);
    json j = { {"DO", DOA}, {"ASprite", ASA}, {"Sprite", SA} };
    o << j;
}

void Scene::addToJSON(json &DOA, json &ASA, json &SA, DisplayObject* dObject){
    //save stuff
    if (dObject->type == "DisplayObject"){
        DOA.push_back({ {"name", dObject->id}, {"filepath", dObject->imgPath}, {"x_pos", dObject->position.x}, {"y_pos", dObject->position.y}, {"rotation", dObject->rotation}, {"scaleX", dObject->scaleX}, {"scaleY", dObject->scaleY}, {"parentId", dObject->parentId} });
    } else if (dObject->type == "Sprite"){
        SA.push_back({ {"name", dObject->id}, {"filepath", dObject->imgPath}, {"x_pos", dObject->position.x}, {"y_pos", dObject->position.y}, {"rotation", dObject->rotation}, {"scaleX", dObject->scaleX}, {"scaleY", dObject->scaleY}, {"parentId", dObject->parentId} });
    } else if (dObject->type == "AnimatedSprite"){
        Animation* temp = ((AnimatedSprite*) dObject)->current;
        ASA.push_back({ {"name", dObject->id}, {"basepath", temp->basepath}, {"animName", temp->animName}, {"numFrames", temp->numFrames}, {"frameRate", temp->frameRate}, {"loop", temp->loop}, {"x_pos", dObject->position.x}, {"y_pos", dObject->position.y}, {"rotation", dObject->rotation}, {"scaleX", dObject->scaleX}, {"scaleY", dObject->scaleY}, {"parentId", dObject->parentId} });
    }

    for (auto* child : dObject->children) {
        addToJSON(DOA, ASA, SA, child);
    }
}
