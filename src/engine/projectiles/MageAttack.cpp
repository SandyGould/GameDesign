#include "MageAttack.h"
#include "../events/EventDispatcher.h"
#include <iostream>

static int mage_attack_count = 1;

MageAttack::MageAttack() : Projectile("mage_attack" + std::to_string(mage_attack_count), "./resources/assets/Animated_Sprites/Enemies/Mage/mageAttack.png", 4){
    mage_attack_count++;
    this->width = 6;
    this->height = 6;
    this->type = "mage_attack";
    this->magic = true;
    this->saveType = this->type;
};

void MageAttack::fire(){
    Projectile::fire(target);
}
