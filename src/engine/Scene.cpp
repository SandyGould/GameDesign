#include "Scene.h"
#include "AnimatedSprite.h"
#include "Layer.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "json.hpp"
using json = nlohmann::json;

using namespace std;

Scene::Scene() : DisplayObject("scene") {}

Scene::Scene(std::shared_ptr<Camera> camera, std::shared_ptr<Player> player) : DisplayObject("scene") {
    this->camera = camera;
    this->player = player;
}

Scene::Scene(std::string id) : DisplayObject(id) {
    this->type = "Scene";
    this->saveType = this->type;
}

	/* Load scene from a file */
void Scene::loadScene(std::string sceneFilePath){
    std::ifstream i(sceneFilePath);
    json j;
    i >> j;

    /* Load camera + player positions */
    this->camEntrancePivot = {j["Camera"]["camEntrancePivotX"], j["Camera"]["camEntrancePivotY"]};
    this->camEntrancePosition = {j["Camera"]["camEntrancePositionX"], j["Camera"]["camEntrancePositionY"]};
    this->playerEntrancePos = {j["Camera"]["playerEntrancePosX"], j["Camera"]["playerEntrancePosY"]};
    this->camExitPivot = {j["Camera"]["camExitPivotX"], j["Camera"]["camExitPivotY"]};
    this->camExitPosition = {j["Camera"]["camExitPositionX"], j["Camera"]["camExitPositionY"]};
    this->playerExitPos = {j["Camera"]["playerExitPosX"], j["Camera"]["playerExitPosY"]};


    for(int z = 0; z < j["Scene"].size(); z++){
        std::string layer_value = "L" + std::to_string(z);
        auto temp_layer = std::make_shared<Layer>(layer_value);
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
            if(obj_type.compare("DisplayObject") == 0){temp_layer->addChild(setBasicInfo(std::make_shared<DisplayObject>(mj["name"], mj["filepath"]), mj));}
            else if(obj_type.compare("AnimatedSprite") == 0){temp_layer->addChild(std::static_pointer_cast<AnimatedSprite>(setBasicInfo(std::make_shared<AnimatedSprite>(mj["name"], mj["sheetpath"], mj["xmlpath"]), mj)));}
            else if(obj_type.compare("Sprite") == 0){temp_layer->addChild(std::static_pointer_cast<Sprite>(setBasicInfo(std::make_shared<Sprite>(mj["name"], mj["filepath"]), mj)));}
            /* enemies */
            else if(obj_type.compare("BaseEnemy") == 0){temp_layer->addChild(std::static_pointer_cast<BaseEnemy>(setBasicInfo(std::make_shared<BaseEnemy>(mj["name"], mj["sheetpath"], mj["xmlpath"], this->player), mj)));}
            else if(obj_type.compare("Archer") == 0){temp_layer->addChild(std::static_pointer_cast<Archer>(setBasicInfo(std::make_shared<Archer>(this->player), mj)));}
            else if(obj_type.compare("KingdomArcher") == 0){temp_layer->addChild(std::static_pointer_cast<KingdomArcher>(setBasicInfo(std::make_shared<KingdomArcher>(this->player), mj)));}
            else if(obj_type.compare("MasterArcher") == 0){temp_layer->addChild(std::static_pointer_cast<MasterArcher>(setBasicInfo(std::make_shared<MasterArcher>(this->player), mj)));}
            else if(obj_type.compare("Cannoneer") == 0){temp_layer->addChild(std::static_pointer_cast<Cannoneer>(setBasicInfo(std::make_shared<Cannoneer>(this->player), mj)));}
            else if(obj_type.compare("RubberCannoneer") == 0){temp_layer->addChild(std::static_pointer_cast<RubberCannoneer>(setBasicInfo(std::make_shared<RubberCannoneer>(this->player), mj)));}
            else if(obj_type.compare("Mage") == 0){temp_layer->addChild(std::static_pointer_cast<Mage>(setBasicInfo(std::make_shared<Mage>(this->player), mj)));}
            else if(obj_type.compare("KingdomMage") == 0){temp_layer->addChild(std::static_pointer_cast<KingdomMage>(setBasicInfo(std::make_shared<KingdomMage>(this->player), mj)));}
            else if(obj_type.compare("Knight") == 0){temp_layer->addChild(std::static_pointer_cast<Knight>(setBasicInfo(std::make_shared<Knight>(this->player), mj)));}
            else if(obj_type.compare("Ogre") == 0){temp_layer->addChild(std::static_pointer_cast<Ogre>(setBasicInfo(std::make_shared<Ogre>(this->player), mj)));}
            else if(obj_type.compare("Orc") == 0){temp_layer->addChild(std::static_pointer_cast<Orc>(setBasicInfo(std::make_shared<Orc>(this->player), mj)));}
            else if(obj_type.compare("Poisoner") == 0){temp_layer->addChild(std::static_pointer_cast<Poisoner>(setBasicInfo(std::make_shared<Poisoner>(this->player), mj)));}
            else if(obj_type.compare("RoarMonster") == 0){temp_layer->addChild(std::static_pointer_cast<RoarMonster>(setBasicInfo(std::make_shared<RoarMonster>(this->player), mj)));}
            else if(obj_type.compare("SecondBoss") == 0){temp_layer->addChild(std::static_pointer_cast<SecondBoss>(setBasicInfo(std::make_shared<SecondBoss>(this->player), mj)));}
            /* environmental objects */
            else if(obj_type.compare("EnvironmentObject") == 0){temp_layer->addChild(std::static_pointer_cast<EnvironmentObject>(setBasicInfo(std::make_shared<EnvironmentObject>(mj["name"], mj["filepath"]), mj)));}
            else if(obj_type.compare("HitObject") == 0){temp_layer->addChild(std::static_pointer_cast<HitObject>(setBasicInfo(std::make_shared<HitObject>(mj["name"], mj["filepath"]), mj)));}
            else if(obj_type.compare("WalkOnObject") == 0){temp_layer->addChild(std::static_pointer_cast<WalkOnObject>(setBasicInfo(std::make_shared<WalkOnObject>(mj["name"], mj["filepath"]), mj)));}
        
        }            
        this->addChild(temp_layer);
    }
}

void Scene::loadScene_Editor(std::string sceneFilePath){
    std::ifstream i(sceneFilePath);
    json j;
    i >> j;
    unordered_set<string> aspr = {"AnimatedSprite", "Archer", "Cannoneer", "Knight", "Mage", "MasterArcher", "Ogre", "Poisoner", "RoarMonster", "RubberCannoneer", "SecondBoss"};
    unordered_set<string> spr = {"Sprite", "EnvironmentObject", "HitObject", "WalkOnObject"};

    for(int z = 0; z < j["Scene"].size(); z++){
        std::string layer_value = "L" + std::to_string(z);
        auto temp_layer = std::make_shared<Layer>(layer_value);
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
            if(obj_type.compare("DisplayObject") == 0){temp_layer->addChild(setBasicInfo(std::make_shared<DisplayObject>(mj["name"], mj["filepath"]), mj));}
            else if(aspr.find(obj_type) != aspr.end()){temp_layer->addChild(std::static_pointer_cast<AnimatedSprite>(setBasicInfo(std::make_shared<AnimatedSprite>(mj["name"], mj["sheetpath"], mj["xmlpath"]), mj)));}
            else if(spr.find(obj_type) != spr.end()){temp_layer->addChild(std::static_pointer_cast<Sprite>(setBasicInfo(std::make_shared<Sprite>(mj["name"], mj["filepath"]), mj)));}
        }            
        this->addChild(temp_layer);
    }
}

std::shared_ptr<DisplayObject> Scene::setBasicInfo(std::shared_ptr<DisplayObject> d_obj, json j){
    d_obj->position.x = j["x_pos"];
    d_obj->position.y = j["y_pos"];
    // d_obj->orig_position.x = j["x_pos"];
    // d_obj->orig_position.y = j["y_pos"];
    d_obj->rotation = j["rotation"];
    d_obj->scaleX = j["scaleX"];
    d_obj->scaleY = j["scaleY"];
    d_obj->saveType = j["type"];
    return d_obj;
}
/*
// Load all objects as DisplayObjects, Sprites, and AnimatedSprites
void Scene::loadScene(std::string sceneFilePath){
    if (!p){
        cout << "No player object, cannot load scene." << endl;
        return;
    }
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
            else if(obj_type.compare("arrow") == 0){
                temp_layer->addChild(generateArrow(json_layer["objects"][y]));
            }
            else if(obj_type.compare("mage_attack") == 0){
                temp_layer->addChild(generateMageAttack(json_layer["objects"][y]));
            }
            else if(obj_type.compare("poison_bomb") == 0){
                temp_layer->addChild(generatePoisonBomb(json_layer["objects"][y]));
            }
            else if(obj_type.compare("rubber_cannonball") == 0){
                temp_layer->addChild(generateRubberCannonBall(json_layer["objects"][y]));
            }
            else if(obj_type.compare("archer") == 0){
                temp_layer->addChild(generateArcher(json_layer["objects"][y]));
            }
            else if(obj_type.compare("cannoneer") == 0){
                temp_layer->addChild(generateCannoneer(json_layer["objects"][y]));
            }
            else if(obj_type.compare("knight") == 0){
                temp_layer->addChild(generateKnight(json_layer["objects"][y]));
            }
            else if(obj_type.compare("mage") == 0){
                temp_layer->addChild(generateMage(json_layer["objects"][y]));
            }
            else if(obj_type.compare("master_archer") == 0){
                temp_layer->addChild(generateMasterArcher(json_layer["objects"][y]));
            }
            else if(obj_type.compare("ogre") == 0){
                temp_layer->addChild(generateOgre(json_layer["objects"][y]));
            }
            else if(obj_type.compare("poisoner") == 0){
                temp_layer->addChild(generatePoisoner(json_layer["objects"][y]));
            }
            else if(obj_type.compare("roar_monster") == 0){
                temp_layer->addChild(generateRoarMonster(json_layer["objects"][y]));
            }
            else if(obj_type.compare("rubber_cannoneer") == 0){
                temp_layer->addChild(generateRubberCannoneer(json_layer["objects"][y]));
            }
            else if(obj_type.compare("second_boss") == 0){
                cout << "here" << endl;
                temp_layer->addChild(generateSecondBoss(json_layer["objects"][y]));
            } else {
                cout << "nowhere" << endl;
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

Arrow* Scene::generateArrow(json j){
    Arrow* temp_arrow = new Arrow(30);
    temp_arrow->position.x = j["x_pos"];
    temp_arrow->position.y = j["y_pos"];
    temp_arrow->orig_position.x = j["x_pos"];
    temp_arrow->orig_position.y = j["y_pos"];
    temp_arrow->rotation = j["rotation"];
    temp_arrow->scaleX = j["scaleX"];
    temp_arrow->scaleY = j["scaleY"];
    return temp_arrow;
}

MageAttack* Scene::generateMageAttack(json j){
    MageAttack* temp_mage_attack = new MageAttack();
    temp_mage_attack->position.x = j["x_pos"];
    temp_mage_attack->position.y = j["y_pos"];
    temp_mage_attack->orig_position.x = j["x_pos"];
    temp_mage_attack->orig_position.y = j["y_pos"];
    temp_mage_attack->rotation = j["rotation"];
    temp_mage_attack->scaleX = j["scaleX"];
    temp_mage_attack->scaleY = j["scaleY"];
    return temp_mage_attack;
}

PoisonBomb* Scene::generatePoisonBomb(json j){
    PoisonBomb* temp_poison_bomb = new PoisonBomb();
    temp_poison_bomb->position.x = j["x_pos"];
    temp_poison_bomb->position.y = j["y_pos"];
    temp_poison_bomb->orig_position.x = j["x_pos"];
    temp_poison_bomb->orig_position.y = j["y_pos"];
    temp_poison_bomb->rotation = j["rotation"];
    temp_poison_bomb->scaleX = j["scaleX"];
    temp_poison_bomb->scaleY = j["scaleY"];
    return temp_poison_bomb;
}

RubberCannonBall* Scene::generateRubberCannonBall(json j){
    RubberCannonBall* temp_rubber_cannonball = new RubberCannonBall(30);
    temp_rubber_cannonball->position.x = j["x_pos"];
    temp_rubber_cannonball->position.y = j["y_pos"];
    temp_rubber_cannonball->orig_position.x = j["x_pos"];
    temp_rubber_cannonball->orig_position.y = j["y_pos"];
    temp_rubber_cannonball->rotation = j["rotation"];
    temp_rubber_cannonball->scaleX = j["scaleX"];
    temp_rubber_cannonball->scaleY = j["scaleY"];
    return temp_rubber_cannonball;
}

Archer* Scene::generateArcher(json j){
    Archer* temp_archer = new Archer(p);
    temp_archer->position.x = j["x_pos"];
    temp_archer->position.y = j["y_pos"];
    temp_archer->orig_position.x = j["x_pos"];
    temp_archer->orig_position.y = j["y_pos"];
    temp_archer->rotation = j["rotation"];
    temp_archer->scaleX = j["scaleX"];
    temp_archer->scaleY = j["scaleY"];
    return temp_archer;
}

Cannoneer* Scene::generateCannoneer(json j){
    Cannoneer* temp_cannoneer = new Cannoneer(p);
    temp_cannoneer->position.x = j["x_pos"];
    temp_cannoneer->position.y = j["y_pos"];
    temp_cannoneer->orig_position.x = j["x_pos"];
    temp_cannoneer->orig_position.y = j["y_pos"];
    temp_cannoneer->rotation = j["rotation"];
    temp_cannoneer->scaleX = j["scaleX"];
    temp_cannoneer->scaleY = j["scaleY"];
    return temp_cannoneer;
}

Knight* Scene::generateKnight(json j){
    Knight* temp_knight = new Knight(p);
    temp_knight->position.x = j["x_pos"];
    temp_knight->position.y = j["y_pos"];
    temp_knight->orig_position.x = j["x_pos"];
    temp_knight->orig_position.y = j["y_pos"];
    temp_knight->rotation = j["rotation"];
    temp_knight->scaleX = j["scaleX"];
    temp_knight->scaleY = j["scaleY"];
    return temp_knight;
}

Mage* Scene::generateMage(json j){
    Mage* temp_mage = new Mage(p);
    temp_mage->position.x = j["x_pos"];
    temp_mage->position.y = j["y_pos"];
    temp_mage->orig_position.x = j["x_pos"];
    temp_mage->orig_position.y = j["y_pos"];
    temp_mage->rotation = j["rotation"];
    temp_mage->scaleX = j["scaleX"];
    temp_mage->scaleY = j["scaleY"];
    return temp_mage;
}

MasterArcher* Scene::generateMasterArcher(json j){
    MasterArcher* temp_master_archer = new MasterArcher(p);
    temp_master_archer->position.x = j["x_pos"];
    temp_master_archer->position.y = j["y_pos"];
    temp_master_archer->orig_position.x = j["x_pos"];
    temp_master_archer->orig_position.y = j["y_pos"];
    temp_master_archer->rotation = j["rotation"];
    temp_master_archer->scaleX = j["scaleX"];
    temp_master_archer->scaleY = j["scaleY"];
    return temp_master_archer;
}

Ogre* Scene::generateOgre(json j){
    Ogre* temp_ogre = new Ogre(p);
    temp_ogre->position.x = j["x_pos"];
    temp_ogre->position.y = j["y_pos"];
    temp_ogre->orig_position.x = j["x_pos"];
    temp_ogre->orig_position.y = j["y_pos"];
    temp_ogre->rotation = j["rotation"];
    temp_ogre->scaleX = j["scaleX"];
    temp_ogre->scaleY = j["scaleY"];
    return temp_ogre;
}

Poisoner* Scene::generatePoisoner(json j){
    Poisoner* temp_poisoner = new Poisoner(p);
    temp_poisoner->position.x = j["x_pos"];
    temp_poisoner->position.y = j["y_pos"];
    temp_poisoner->orig_position.x = j["x_pos"];
    temp_poisoner->orig_position.y = j["y_pos"];
    temp_poisoner->rotation = j["rotation"];
    temp_poisoner->scaleX = j["scaleX"];
    temp_poisoner->scaleY = j["scaleY"];
    return temp_poisoner;
}

RoarMonster* Scene::generateRoarMonster(json j){
    RoarMonster* temp_roar_monster = new RoarMonster(p);
    temp_roar_monster->position.x = j["x_pos"];
    temp_roar_monster->position.y = j["y_pos"];
    temp_roar_monster->orig_position.x = j["x_pos"];
    temp_roar_monster->orig_position.y = j["y_pos"];
    temp_roar_monster->rotation = j["rotation"];
    temp_roar_monster->scaleX = j["scaleX"];
    temp_roar_monster->scaleY = j["scaleY"];
    return temp_roar_monster;
}

RubberCannoneer* Scene::generateRubberCannoneer(json j){
    RubberCannoneer* temp_rubber_cannoneer = new RubberCannoneer(p);
    temp_rubber_cannoneer->position.x = j["x_pos"];
    temp_rubber_cannoneer->position.y = j["y_pos"];
    temp_rubber_cannoneer->orig_position.x = j["x_pos"];
    temp_rubber_cannoneer->orig_position.y = j["y_pos"];
    temp_rubber_cannoneer->rotation = j["rotation"];
    temp_rubber_cannoneer->scaleX = j["scaleX"];
    temp_rubber_cannoneer->scaleY = j["scaleY"];
    return temp_rubber_cannoneer;
}

SecondBoss* Scene::generateSecondBoss(json j){
    SecondBoss* temp_second_boss = new SecondBoss(p);
    temp_second_boss->position.x = j["x_pos"];
    temp_second_boss->position.y = j["y_pos"];
    temp_second_boss->orig_position.x = j["x_pos"];
    temp_second_boss->orig_position.y = j["y_pos"];
    temp_second_boss->rotation = j["rotation"];
    temp_second_boss->scaleX = j["scaleX"];
    temp_second_boss->scaleY = j["scaleY"];
    return temp_second_boss;
}*/

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

void Scene::addToJSON(json &Layer, std::shared_ptr<DisplayObject> dObject){
    if (dObject){
        for (auto child : dObject->children){
            std::vector<std::string> tempVec;
            auto tempDO = child->parent;
            while (tempDO != nullptr){
                tempVec.push_back(tempDO->id);
                tempDO = tempDO->parent;
            }
            if (child->type == "AnimatedSprite"){
                auto tempAS = std::static_pointer_cast<AnimatedSprite>(child);
                Layer.push_back({ {"type", tempAS->saveType}, {"name", tempAS->id}, {"sheetpath", tempAS->sheetpath}, {"xmlpath", tempAS->xmlpath}, {"x_pos", tempAS->position.x}, {"y_pos", tempAS->position.y}, {"rotation", tempAS->rotation}, {"scaleX", tempAS->scaleX}, {"scaleY", tempAS->scaleY} /*,{"parentHierarchy", tempVec}*/ });
            } else{
                Layer.push_back({ {"type", child->saveType}, {"name", child->id}, {"filepath", child->imgPath}, {"x_pos", child->position.x}, {"y_pos", child->position.y}, {"rotation", child->rotation}, {"scaleX", child->scaleX}, {"scaleY", child->scaleY} /*,{"parentHierarchy", tempVec}*/ });
            }
            addToJSON(Layer, child);
        }
    }
}

void Scene::update(const unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const unordered_set<Uint8>& pressedButtons){
    DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}

void Scene::draw(AffineTransform& at) {
    DisplayObject::draw(at);
}