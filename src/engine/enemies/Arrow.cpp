#include "Arrow.h"
#include <iostream>

int arrow_id_counter = 1;

Arrow::Arrow(int velocity) : Projectile("Arrow" + std::to_string(arrow_id_counter), "./resources/assets/Animated_Sprites/Enemies/Mage/mageAttack.png", velocity){
    arrow_id_counter++;
    // this->scaleX = 0.25;
    // this->scaleY = 0.25;
    this->hasCollision = true;
    this->type = "arrow";
    this->saveType = this->type;
    this->visible = true;
}

void Arrow::drawBack(){
    //TODO: make this work for whatevr direction the sprite is facing :)
    this->position.x-=4;
}

void Arrow::draw(AffineTransform& at) {
    Projectile::draw(at);
}
