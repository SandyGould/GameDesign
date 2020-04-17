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

Scene::Scene() : DisplayObject("scene") {}

Scene::Scene(Camera* camera, Player* player) : DisplayObject("scene") {
    this->camera = camera;
    this->player = player;
}

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
        temp_layer->cam = this->camera;
        for(int y = 0; y < json_layer["objects"].size(); ++y){
            // std::cout << "type: " + json_layer["objects"][y]["type"].get<std::string>() << std::endl;
            
            // DisplayObjectContainer* parent = temp_layer;
            // if(json_layer["objects"][y]["parentHierarchy"].size() > 0){
            //     parent = find_parent(json_layer["objects"][y]["parentHierarchy"], temp_layer);
            // } 

            std::string obj_type = json_layer["objects"][y]["type"].get<std::string>();
            json mj = json_layer["objects"][y];
            if(obj_type.compare("DisplayObject") == 0){temp_layer->addChild(setBasicInfo(new DisplayObject(mj["name"], mj["filepath"]), mj));}
            else if(obj_type.compare("AnimatedSprite") == 0){temp_layer->addChild((AnimatedSprite*)setBasicInfo(new AnimatedSprite(mj["name"], mj["sheetpath"], mj["xmlpath"]), mj));}
            else if(obj_type.compare("Sprite") == 0){temp_layer->addChild((Sprite*)setBasicInfo(new Sprite(mj["name"], mj["filepath"]), mj));}
            /* enemies */
            else if(obj_type.compare("BaseEnemy") == 0){temp_layer->addChild((BaseEnemy*)setBasicInfo(new BaseEnemy(mj["name"], mj["sheetpath"], mj["xmlpath"], this->player), mj));}
            else if(obj_type.compare("Archer") == 0){temp_layer->addChild((Archer*)setBasicInfo(new Archer(this->player), mj));}
            else if(obj_type.compare("KingdomArcher") == 0){temp_layer->addChild((KingdomArcher*)setBasicInfo(new KingdomArcher(this->player), mj));}
            else if(obj_type.compare("MasterArcher") == 0){temp_layer->addChild((MasterArcher*)setBasicInfo(new MasterArcher(this->player), mj));}
            else if(obj_type.compare("Cannoneer") == 0){temp_layer->addChild((Cannoneer*)setBasicInfo(new Cannoneer(this->player), mj));}
            else if(obj_type.compare("RubberCannoneer") == 0){temp_layer->addChild((RubberCannoneer*)setBasicInfo(new RubberCannoneer(this->player), mj));}
            else if(obj_type.compare("Mage") == 0){temp_layer->addChild((Mage*)setBasicInfo(new Mage(this->player), mj));}
            else if(obj_type.compare("KingdomMage") == 0){temp_layer->addChild((KingdomMage*)setBasicInfo(new KingdomMage(this->player), mj));}
            else if(obj_type.compare("Knight") == 0){temp_layer->addChild((Knight*)setBasicInfo(new Knight(this->player), mj));}
            else if(obj_type.compare("Ogre") == 0){temp_layer->addChild((Ogre*)setBasicInfo(new Ogre(this->player), mj));}
            else if(obj_type.compare("Orc") == 0){temp_layer->addChild((Orc*)setBasicInfo(new Orc(this->player), mj));}
            else if(obj_type.compare("Poisoner") == 0){temp_layer->addChild((Poisoner*)setBasicInfo(new Poisoner(this->player), mj));}
            else if(obj_type.compare("RoarMonster") == 0){temp_layer->addChild((RoarMonster*)setBasicInfo(new RoarMonster(this->player), mj));}
            else if(obj_type.compare("SecondBoss") == 0){temp_layer->addChild((SecondBoss*)setBasicInfo(new SecondBoss(this->player), mj));}
            /* environmental objects */
            else if(obj_type.compare("EnvironmentObject") == 0){temp_layer->addChild((EnvironmentObject*)setBasicInfo(new EnvironmentObject(mj["name"], mj["filepath"]), mj));}
            else if(obj_type.compare("HitObject") == 0){temp_layer->addChild((HitObject*)setBasicInfo(new HitObject(mj["name"], mj["filepath"]), mj));}
            else if(obj_type.compare("WalkOnObject") == 0){temp_layer->addChild((WalkOnObject*)setBasicInfo(new WalkOnObject(mj["name"], mj["filepath"]), mj));}
        
        }            
        this->addChild(temp_layer);
    }
}

DisplayObject* Scene::setBasicInfo(DisplayObject* d_obj, json j){
    d_obj->position.x = j["x_pos"];
    d_obj->position.y = j["y_pos"];
    // d_obj->orig_position.x = j["x_pos"];
    // d_obj->orig_position.y = j["y_pos"];
    d_obj->rotation = j["rotation"];
    d_obj->scaleX = j["scaleX"];
    d_obj->scaleY = j["scaleY"];
    return d_obj;
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

// void Scene::setCameraRef(Camera* camera){
//     for (auto child : children) {
//         if (child->type == "layer"){
//             Layer* temp_layer = (Layer*)child;
//             temp_layer->cam = camera;
//         }
//     }
// }

// void Scene::obtainPlayerRef(Player* player){
//     this->player = player;
// }

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