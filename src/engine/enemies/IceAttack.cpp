#include "IceAttack.h"
#include "../events/EventDispatcher.h"
#include <iostream>

IceAttack::IceAttack() : Projectile("ice_attack", "./resources/assets/Animated_Sprites/Enemies/iceAttack.png", 10){
    this->width = 50;
    this->height= 50;
    this->type = "ice_attack";
    this->saveType = this->type;
};

void IceAttack::fire(){
    Projectile::fire(target);
}
