#include "Scene.h"
#include "AnimatedSprite.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <json.hpp>

using json = nlohmann::json;

Scene::Scene() : DisplayObjectContainer(){
    this->type = "Scene";
}
Scene::Scene(std::string id) : DisplayObjectContainer(){
    this->type = "Scene";
    this->id = id;
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
        DisplayObjectContainer *temp_layer = new DisplayObjectContainer();
        std::string layer_value = "L" + std::to_string(z);
        json json_layer = j["Scene"][z][layer_value];

        temp_layer->parallaxSpeed = json_layer["speed"];

        for(int y = 0; y < json_layer["objects"].size(); y++){
            // std::cout << "type: " + json_layer["objects"][y]["type"].get<std::string>() << std::endl;
            
            // DisplayObjectContainer* parent = temp_layer;
            // if(json_layer["objects"][y]["parentHierarchy"].size() > 0){
            //     parent = find_parent(json_layer["objects"][y]["parentHierarchy"], temp_layer);
            // } 

            std::string obj_type = json_layer["objects"][y]["type"].get<std::string>();
            if(obj_type.compare("DOC") == 0){
                temp_layer->addChild(generateDOC(json_layer["objects"][y]));
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

DisplayObjectContainer* Scene::generateDOC(json j){
    DisplayObjectContainer* temp_doc = new DisplayObjectContainer(j["name"], j["filepath"]);
    temp_doc->position.x = j["x_pos"];
    temp_doc->position.y = j["y_pos"];
    temp_doc->rotation = j["rotation"];
    temp_doc->scaleX = j["scaleX"];
    temp_doc->scaleY = j["scaleY"];
    return temp_doc;
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

void Scene::update(std::set<SDL_Scancode> pressedKeys){
    DisplayObjectContainer::update(pressedKeys);
}
void Scene::draw(AffineTransform &at){
    DisplayObjectContainer::draw(at);
}