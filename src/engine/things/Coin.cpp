#include "Coin.h"
#include "../events/Collision.h"
#include "../events/Event.h"

int coin_id_counter = 1;

Coin::Coin() : Sprite("coin_"+std::to_string(coin_id_counter) , "./resources/solarSystem/Planet.png"){
    ++coin_id_counter;
    hasCollision = true;
}

void Coin::update(std::set<SDL_Scancode> pressedKeys){
    Sprite::update(pressedKeys);
}

void Coin::draw(AffineTransform& at){
    Sprite::draw(at);
}

void Coin::handleEvent(Event* e){
    if (e->getType() == "collision"){
        if(((Collision*) e)->getDOID() == this->id){
            this->visible = false;
        }
    }
}