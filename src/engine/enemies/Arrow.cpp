#include "Arrow.h"
#include <iostream>

int arrow_id_counter = 1;

Arrow::Arrow(int velocity) : Projectile("Arrow" + std::to_string(arrow_id_counter), "./resources/assets/Animated_Sprites/Enemies/arrow.png", velocity){
    arrow_id_counter++;
    // this->scaleX = 0.25;
    // this->scaleY = 0.25;
    this->height = this->width = 24;
    this->hasCollision = true;
    this->type = "arrow";
    this->saveType = this->type;
    this->visible = true;
}

void Arrow::drawBack(){
    //TODO: make this work for whatevr direction the sprite is facing :)
    this->position.x -= 1;
}

double Arrow::aim(std::shared_ptr<DisplayObject> targetSprite) {
    double angle = Projectile::aim(targetSprite);
    this->rotation = angle + 3*PI/4;
    return angle;
}

void Arrow::draw(AffineTransform& at) {
    Projectile::draw(at);
}
