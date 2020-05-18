#include "PoisonBomb.h"

#include "../enemies/BaseEnemy.h"
#include "../things/Player.h"

#include <iostream>

static int poison_bomb_count = 1;

PoisonBomb::PoisonBomb() : Sprite("bomb" + std::to_string(poison_bomb_count), "./resources/assets/Display_Objects/PoisonBomb.png"){
    poison_bomb_count++;
    radius = 10;
    this->height = 50;
    this->width = 50;
    this->type = "poison_bomb";
    this->hitboxType = HitboxType::Circle;
    this->saveType = this->type;
}


void PoisonBomb::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
    if (Game::instance->paused) {
        return;
    }
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
        this->exploding = true;
        this->alpha = 50;
    }
    if(this->explosionTime == 0){
        this->removeThis();
    }
    this->scaleX+= 0.5;
    this->scaleY+= 0.5;
    this->explosionTime--;
}

bool PoisonBomb::onCollision(std::shared_ptr<DisplayObject> other, CollisionDirection direction1, CollisionDirection direction2) {
    if(this->exploding){
        if(other->type == "player"){
            std::static_pointer_cast<Player>(other)->changeHealth(-1);
            return true;
        }
        else if((other->type == "enemy")||(other->type == "knight")||(other->type == "ogre")){
            std::static_pointer_cast<BaseEnemy>(other)->changeHealth(-1);
            return true;
        }
    }
    return true;
}
