#include "Mage.h"
#include "MageAttack.h"
#include <math.h>
#include <iostream>
#include "../events/EventDispatcher.h"

Mage::Mage(Player* player) : BaseEnemy("mage", "./resources/assets/Animated_Sprites/Enemies/Mage/Mage.png", player) {
    hasCollision = true;
}

Mage::Mage(Player* player, std::string filepath) :BaseEnemy("mage", filepath, player){

}

/*
Init
Wait for player
Aim
Fire Attack
Reload
Ded
*/
void Mage::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
   if(this->health ==0){
        this->clean = true;
    }
    if(this->clean){
        //cleanup
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
        this->ready--;
        this->mageAttack = new MageAttack();
       // std::cout<<"target"<<mageAttack->target<<"\n";
        if(this->ready==240){
            this->mageAttack->target = this->mageAttack->aim(player);
            this->state = 3;
        }
    }
    else if(this->state == 3){
 		this->addChild(mageAttack);
        this->ready--;
        if(this->ready == 0){
            this->mageAttack->fire();
            this->ready = 301;
            this->state = 2;
        }
    }
    BaseEnemy::update(pressedKeys, joystickState, pressedButtons);
}