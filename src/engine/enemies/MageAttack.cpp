#include "MageAttack.h"
#include "../events/EventDispatcher.h"
#include <iostream>

MageAttack::MageAttack() : Projectile("mage_attack", "./resources/assets/Animated_Sprites/Enemies/Mage/mageAttack.png", 25){
    this->width = 30;
    this->height= 30;
    this->type = "mage_attack";
};

void MageAttack::fire(){
    Projectile::fire(target);
}