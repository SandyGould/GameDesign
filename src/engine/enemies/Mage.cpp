#include "Mage.h"

#include <iostream>

Mage::Mage(Player* player) : BaseEnemy("mage", "./resources/assets/Animated_Sprites/Enemies/Mage/Mage.png", "", player) {
    hasCollision = true;
    this->saveType = "mage";
    this->mageAttack = nullptr;
}

Mage::Mage(Player* player, std::string filepath, std::string xml): BaseEnemy("kMage", filepath, xml, player){
    
}

/*
Init
Wait for player
Aim
Fire Attack
Reload
Ded*/
void Mage::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
    if(this->health <= 0) {
        this->removeThis();
        return;
    }

    if(this->state == 0){
        this->ready =301;
        this->state = 1;
    }
    else if(this->state ==1){
        //wait for player
        this->state = 2;
    }
    else if(this->state == 2){
        if(this->ready == 301){
            this->mageAttack = new MageAttack();
        }
        this->ready--;
 		this->addChild(mageAttack);
        mageAttack->visible =false;
        if(this->ready==240){
            this->mageAttack->target = this->mageAttack->aim(player);
            mageAttack->visible=true;
            this->state = 3;
        }
    }
    else if(this->state == 3){
        this->ready--;
        if(this->ready == 0){
            this->mageAttack->fire();
            this->ready = 301;
            this->state = 2;
        }
    }

    BaseEnemy::update(pressedKeys, joystickState, pressedButtons);
}

bool Mage::onCollision(DisplayObject* other){
    if(other == this->mageAttack && mageAttack->firing == false){
        return true;
    }
    return BaseEnemy::onCollision(other);
}
