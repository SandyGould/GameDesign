#include "Arrow.h"
#include <iostream>

static int arrow_id_counter = 1;

Arrow::Arrow(int velocity):Projectile("Arrow"+arrow_id_counter, "./resources/assets/Animated_Sprites/Enemies/Mage/mageAttack.png", velocity){
    arrow_id_counter++;
    this->scaleX = 0.25;
    this->scaleY = 0.25;
    //pivot = {width/2, height/2};
}


void Arrow::drawBack(){
    //TODO: make some decisons on this; may switch order of attacking lol.
        this->position.x-=4;
        this->position.y-=4;
}