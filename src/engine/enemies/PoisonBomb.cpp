#include "PoisonBomb.h"
#include <iostream>

PoisonBomb::PoisonBomb():Sprite("bomb", "./resources/assets/Display_Objects/Planet.png"){
    radius = 10;
    this->type = "poison_bomb";
    this->saveType = this->type;
}

PoisonBomb::~PoisonBomb(){
    //Sprite::~Sprite();
}

void PoisonBomb::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
    if(timer == 0){
        this->explode();
    }
    timer--;
    Sprite::update(pressedKeys, joystickState, pressedButtons);
}

void PoisonBomb::explode(){
    this->visible = false;
    if(this->explosionTime == 0){
        this->parent->removeImmediateChild(this);
        delete this;
    }
    this->scaleX++;
    this->scaleY++;
    this->explosionTime--;
}
