#include "BaseEnemy.h"
#include <iostream>

BaseEnemy::BaseEnemy(std::string id, std::string spritesheet, std::string xml, Player* player) : AnimatedSprite(id, spritesheet, xml){
    hasCollision=true;
    this->player = player;
    this->type = "enemy";
}

void BaseEnemy::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
    AnimatedSprite::update(pressedKeys,joystickState,pressedButtons);
}

void  BaseEnemy::draw(AffineTransform& at){
    AnimatedSprite::draw(at);
}

void BaseEnemy::changeHealth(int amount){
    this->health+=amount;
}

bool BaseEnemy::onCollision(DisplayObject* other){
     if(other->type == "mage_attack" || other->type == "arrow"){
        this->changeHealth(-20);
        other->removeThis();
        return true;
    }
    if(other->type == "rubber_cannonball" || other->type == "cannonball"){
        this->changeHealth(-100);
        return true;
    }
    return false;
}

void BaseEnemy::cleanUp(){
        for(DisplayObject* object: children){
            this->removeImmediateChild(object);
        }
        this->removeThis();
}
