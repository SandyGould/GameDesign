#include "Arrow.h"
#include <iostream>

int arrow_id_counter = 1;

Arrow::Arrow(int velocity):Projectile("Arrow"+arrow_id_counter, "./resources/assets/Animated_Sprites/Enemies/Mage/mageAttack.png", velocity){
    arrow_id_counter++;
    facingRight = false;
}


void Arrow::drawBack(){
    if(facingRight){
        this->position.x-=10;
    }
    else{
        this->position.x+=10;
    }
}