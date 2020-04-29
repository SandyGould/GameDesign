#include "MageAttack.h"
#include "../events/EventDispatcher.h"
#include <iostream>

MageAttack::MageAttack() : Projectile("mage_attack", "./resources/assets/Animated_Sprites/Enemies/Mage/mageAttack.png", 12){
    this->width = 6;
    this->height = 6;
    this->type = "mage_attack";
    this->magic = true;
    this->saveType = this->type;
};

void MageAttack::fire(){
    Projectile::fire(target);
}
