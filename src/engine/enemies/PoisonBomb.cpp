#include "PoisonBomb.h"
#include <iostream>

PoisonBomb::PoisonBomb():Sprite("bomb", "./resources/assets/Display_Objects/Planet.png"){
    radius = 10;
    this->type = "poison_bomb";
    this->hitboxType = HitboxType::Circle;
}

void PoisonBomb::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons){
    if(timer == 0){
        this->explode();
    }
    else{
        timer--;
    }
    Sprite::update(pressedKeys, joystickState, pressedButtons);
}

void PoisonBomb::explode(){
    if(this->explosionTime==6 ){
//        this->setTexture("./resources/assets/Display_Objects/Moon.png");
//      //  this->loadTexture("./resources/assets/Display_Objects/Moon.png", Game::renderer);
        this->visible = false;
    }
    if(this->explosionTime == 0){
        std::cout<<"Boom\n";
        //this->parent->removeImmediateChild(this);
    }
    this->scaleX++;
    this->scaleY++;
    this->explosionTime--;
}
