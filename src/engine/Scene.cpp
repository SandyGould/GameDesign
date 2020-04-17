#include "Scene.h"
#include "AnimatedSprite.h"
#include "Layer.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "json.hpp"
#include "events/NewSceneEvent.h"
#include "tweens/TweenJuggler.h"
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
        Layer* temp_layer = new Layer(layer_value);
        json json_layer = j["Scene"][z][layer_value];
        temp_layer->parallaxSpeed = json_layer["speed"];
        
        for(int y = 0; y < json_layer["objects"].size(); ++y){
            // std::cout << "type: " + json_layer["objects"][y]["type"].get<std::string>() << std::endl;
            
            // DisplayObjectContainer* parent = temp_layer;
            // if(json_layer["objects"][y]["parentHierarchy"].size() > 0){
            //     parent = find_parent(json_layer["objects"][y]["parentHierarchy"], temp_layer);
            // } 

            std::string obj_type = json_layer["objects"][y]["type"].get<std::string>();
            if(obj_type.compare("DisplayObject") == 0){
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
    temp_do->orig_position.x = j["x_pos"];
    temp_do->orig_position.y = j["y_pos"];
    temp_do->rotation = j["rotation"];
    temp_do->scaleX = j["scaleX"];
    temp_do->scaleY = j["scaleY"];
    return temp_do;
}

AnimatedSprite* Scene::generateAS(json j){
    AnimatedSprite* temp_asprite = new AnimatedSprite(j["name"], j["sheetpath"], j["xmlpath"]);
    temp_asprite->position.x = j["x_pos"];
    temp_asprite->position.y = j["y_pos"];
    temp_asprite->orig_position.x = j["x_pos"];
    temp_asprite->orig_position.y = j["y_pos"];
    temp_asprite->rotation = j["rotation"];
    temp_asprite->scaleX = j["scaleX"];
    temp_asprite->scaleY = j["scaleY"];
    return temp_asprite;
}

Sprite* Scene::generateSprite(json j){
    Sprite* temp_sprite = new Sprite(j["name"], j["filepath"]);
    temp_sprite->position.x = j["x_pos"];
    temp_sprite->position.y = j["y_pos"];
    temp_sprite->orig_position.x = j["x_pos"];
    temp_sprite->orig_position.y = j["y_pos"];
    temp_sprite->rotation = j["rotation"];
    temp_sprite->scaleX = j["scaleX"];
    temp_sprite->scaleY = j["scaleY"];
    return temp_sprite;
}

void Scene::saveScene(std::string sceneName){
    std::ofstream o("./resources/scene/" + sceneName);
    json L0A = json::array();
    json L1A = json::array();
    json L2A = json::array();
    addToJSON(L0A, this->getChild(0));
    addToJSON(L1A, this->getChild(1));
    addToJSON(L2A, this->getChild(2));
    json L0 = { {"speed", this->getChild(0)->parallaxSpeed}, {"objects", L0A} };
    json L1 = { {"speed", this->getChild(1)->parallaxSpeed}, {"objects", L1A} };
    json L2 = { {"speed", this->getChild(2)->parallaxSpeed}, {"objects", L2A} };
    json L0C = { {"L0", L0} };
    json L1C = { {"L1", L1} };
    json L2C = { {"L2", L2} };
    json j = json::array();
    j.push_back(L0C);
    j.push_back(L1C);
    j.push_back(L2C);
    json j2 = { {"Scene", j} };
    o << j2;
}

void Scene::addToJSON(json &Layer, DisplayObject* dObject){
    if (dObject){
        for (auto* child : dObject->children){
            std::vector<std::string> tempVec;
            DisplayObject* tempDO = child->parent;
            while (tempDO != NULL){
                tempVec.push_back(tempDO->id);
                tempDO = tempDO->parent;
            }
            if (child->type == "AnimatedSprite"){
                AnimatedSprite* tempAS = (AnimatedSprite*) child;
                Layer.push_back({ {"type", tempAS->type}, {"name", tempAS->id}, {"sheetpath", tempAS->sheetpath}, {"xmlpath", tempAS->xmlpath}, {"x_pos", tempAS->position.x}, {"y_pos", tempAS->position.y}, {"rotation", tempAS->rotation}, {"scaleX", tempAS->scaleX}, {"scaleY", tempAS->scaleY} /*,{"parentHierarchy", tempVec}*/ });
            } else{
                Layer.push_back({ {"type", child->type}, {"name", child->id}, {"filepath", child->imgPath}, {"x_pos", child->position.x}, {"y_pos", child->position.y}, {"rotation", child->rotation}, {"scaleX", child->scaleX}, {"scaleY", child->scaleY} /*,{"parentHierarchy", tempVec}*/ });
            }
            addToJSON(Layer, child);
        }
    }
}

void Scene::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons){
    DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}

void Scene::draw(AffineTransform& at) {
    DisplayObject::draw(at);
}

void Scene::setCameraRef(Camera* camera){
    for (auto child : children) {
        if (child->type == "layer"){
            Layer* temp_layer = (Layer*)child;
            temp_layer->cam = camera;
        }
    }
}

void Scene::handleEvent(Event* e){
	if (e->getType() == NewSceneEvent::OUT_SCENE_EVENT){
		EventDispatcher::getInstance().removeEventListener(this, NewSceneEvent::OUT_SCENE_EVENT);
        Tween * start_transition = new Tween("start_transition", this);
		start_transition->animate(TweenableParams::SCALE_X, 1, 0, 100, TweenParam::EASE_IN);
		start_transition->animate(TweenableParams::SCALE_Y, 1, 0, 100, TweenParam::EASE_IN);
		TweenJuggler::getInstance().add(start_transition);
	}
    if (e->getType() == NewSceneEvent::IN_SCENE_EVENT){
        EventDispatcher::getInstance().removeEventListener(this, NewSceneEvent::IN_SCENE_EVENT);
        Tween * start_transition = new Tween("start_transition", this);
		start_transition->animate(TweenableParams::SCALE_X, 1, 0, 100, TweenParam::EASE_IN);
		start_transition->animate(TweenableParams::SCALE_Y, 1, 0, 100, TweenParam::EASE_IN);
		TweenJuggler::getInstance().add(start_transition);
	}
    // define other scene transitions here if we want them!
}