#include "Arrow.h"
#include <iostream>

int arrow_id_counter = 1;

Arrow::Arrow(int velocity):Projectile("Arrow"+arrow_id_counter, "./resources/assets/Animated_Sprites/Enemies/Mage/mageAttack.png", velocity){
    arrow_id_counter++;
    this->scaleX = 0.25;
    this->scaleY = 0.25;
    this->hasCollision = true;
    this->type = "arrow";
}

void Arrow::drawBack(){
    //TODO: make this work for whatevr direction the sprite is facing :)
    this->position.x-=4;
}