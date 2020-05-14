#include "IceAttack.h"
#include "../events/EventDispatcher.h"
#include <iostream>

static int ice_attack_count = 1;

IceAttack::IceAttack() : Projectile("ice_attack" + std::to_string(ice_attack_count), "./resources/assets/Animated_Sprites/Enemies/iceAttack.png", 10){
    ice_attack_count++;
    this->width = 50;
    this->height= 50;
    this->type = "ice_attack";
    this->magic = true;
    this->saveType = this->type;
};

void IceAttack::fire(){
    Projectile::fire(target);
}
